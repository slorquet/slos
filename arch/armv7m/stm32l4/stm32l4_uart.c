#include "config.h"

#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <termios.h>
#include <slos/uart.h>
#include <slos/stdio.h>

#include "armv7m.h"
#include "bits/stm32f1_periphs.h"
#include "bits/stm32l4_rcc.h"
#include "bits/stm32f1_gpio.h"
#include "bits/stm32l4_uart.h"
#include "bits/irq.h"
#include "stm32l4_gpio.h"
#include "stm32l4_rcc.h"
#include "stm32l4_uart.h"

/*==============================================================================
 * Types
 *==============================================================================
 */

struct stm32l4_uartparams_s
{
  uint32_t base;
  uint32_t ckenreg;
  uint32_t ckenbit;
  uint32_t txpin;
  uint32_t rxpin;
  uint8_t  irq;    /* irq line */
  uint8_t  is_kconsole:1; /* set to one if this uart is the kernel console */
};

struct stm32l4_uart_s
{
  struct uart_s                      uart; /* MUST be the first field */
  const struct stm32l4_uartparams_s *params; /*constant values */
  /*other variable values*/
  uint8_t                            drivemode; /* none, irq, dma */
};

/*==============================================================================
 * Function Prototypes
 *==============================================================================
 */

static int stm32l4_uart_init (struct uart_s *uart);
static int stm32l4_uart_fini (struct uart_s *uart);
static int stm32l4_uart_write(struct uart_s *uart, const uint8_t *buf, int len);
static int stm32l4_uart_flush(struct uart_s *uart);
static int stm32l4_uart_avail(struct uart_s *uart);
static int stm32l4_uart_read (struct uart_s *uart, uint8_t *buf, int len);
static int stm32l4_uart_ioctl(struct uart_s *uart, int command, void* params);

static int  kputs(const char *data, void *arg);
static void kputc(const char data, void *arg);

/*==============================================================================
 * Variables and constants
 *==============================================================================
 */
static const struct uart_ops_s g_stm32l4_uartops =
{
  stm32l4_uart_init,
  stm32l4_uart_fini,
  stm32l4_uart_write,
  stm32l4_uart_flush,
  stm32l4_uart_avail,
  stm32l4_uart_read,
  stm32l4_uart_ioctl,
};

#ifdef CONFIG_STM32L4_USART1
static const struct stm32f1_uartparams_s g_stm32f1_usart1params =
{
  .regbase    = STM32L4_REGBASE_USART1,
  .rccreg     = STM32L4_RCC_APB2ENR,
  .rccbit     = RCC_APB2ENR_USART1,

  .irq        = STM32L4_IRQ_USART1,
#ifdef CONFIG_STM32L4_USART1_KCONSOLE
  .is_kconsole = 1,
#else
  .is_kconsole = 0,
#endif
  .txpin      = GPIO_PORT_B | GPIO_PIN_6 | GPIO_MODE_ALT | GPIO_SPEED_MED | GPIO_TYPE_PP,
  .rxpin      = GPIO_PORT_B | GPIO_PIN_7 | GPIO_MODE_IN  | GPIO_SPEED_MED | GPIO_PULL_UP,
};

static struct stm32f1_uart_s g_stm32f1_usart1 =
{
  .uart =
    {
      .ops          = &g_stm32f1_uartops,

      .term.c_baud  = CONFIG_STM32F1_USART1_BAUDRATE,

#ifdef CONFIG_STM32L4_USART1_KCONSOLE
      .term.c_oflag = ONLCR,
#else
      .term.c_oflag = 0,
#endif

#if defined( CONFIG_STM32L4_USART1_PARITY_NONE )
      .term.c_cflag = 0
#elif defined( CONFIG_STM32L4_USART1_PARITY_ODD )
      .parity   = PARENB | PARODD
#elif defined( CONFIG_STM32L4_USART1_PARITY_EVEN )
      .parity   = PARENB
#else
#error undefined USART1 parity
#endif
#if CONFIG_STM32L4_USART1_STOPBITS == 1
                , /* No additional control flags */
#elif CONFIG_STM32L4_USART1_STOPBITS == 2
                | CSTOPB,
#else
#error unsupported stop bits
#endif
    },

    .params = &g_stm32l4_usart1params,
    .drivemode = DRIVEMODE_BASIC
};
#endif

static const struct stm32l4_uart_s *g_stm32l4_uarts[] = {
#ifdef CONFIG_STM32L4_USART1
  &g_stm32l4_usart1,
#else
  NULL,
#endif
#ifdef CONFIG_STM32L4_USART2
  &g_stm32l4_usart2,
#else
  NULL,
#endif
#ifdef CONFIG_STM32L4_USART3
  &g_stm32l4_usart3,
#else
  NULL,
#endif
#ifdef CONFIG_STM32L4_UART4
  &g_stm32l4_uart4,
#else
  NULL,
#endif
#ifdef CONFIG_STM32L4_UART5
  &_stm32l4_uart5,
#else
  NULL,
#endif
};

/* Create an enum to count uarts, because sizeof(uarts[0]) will not work if there are no uarts */
enum
{
#ifdef CONFIG_STM32L4_USART1
  STM32L4_INDEX_USART1,
#endif
  STM32L4_UARTCOUNT
};

static struct stm32l4_uart_s *g_stm32f1_kconsole;

/* Stream structure used by the kprintf function in libc */
const struct printf_stream_s konsole =
{
  .putchar = kputc,
  .puts    = kputs
};

/*==============================================================================
 * Functions
 *==============================================================================
 */

/*----------------------------------------------------------------------------*/
static inline uint32_t stm32l4_uart_getreg(const struct stm32l4_uart_s *uart, uint32_t regoff)
{
  return getreg32(uart->base + regoff);
}

/*----------------------------------------------------------------------------*/
static inline void stm32l4_uart_putreg(const struct stm32l4_uart_s *uart, uint32_t regoff, uint32_t value)
{
  putreg32(uart->base + regoff, value);
}

/*----------------------------------------------------------------------------*/
/*
 * Fclk      baud      float     int(16times) hex   int part   frac part      approximated
 * 16 MHz    115200    8,68055   138          0x8A  8          10/16 = 0.625  8.625
 */
void stm32l4_uart_setbaudrate(uint32_t uartid, uint32_t baud)
{
  const struct stm32l4_uart_s *uart;

  if (uartid>(sizeof(g_stm32l4_uarts)/sizeof(g_stm32l4_uarts[0])))
    {
      return;
    }

  uart = g_stm32l4_uarts[uartid];
  if (uart==NULL)
    {
      return;
    }

  /*
   * Compute using current value for clock, assuming OVER8=0
   * BAUD = fclk / (16 x DIV)
   * 16 x DIV x BAUD = fclk
   * DIVfloat = fclk / (16 x BAUD) (DIV is a FLOAT)
   * DIVint   = (16 x fclk) / (16 x BAUD) (DIV is a INT with 4-bit frac part)
   * DIVint   = fclk / BAUD (DIV is a INT with 4-bit frac part)
   */

  /* Divide */
  baud = stm32l4_clock_get() / baud;

  /* Mask high bits */
  baud &= 0xFFFF;
  stm32l4_uart_putreg(uart, STM32L4_USART_BRR, baud);
}

/*----------------------------------------------------------------------------*/
void stm32l4_uart_init(struct uart_s *uart)
{
  uint32_t base;
  uint32_t reg;
  uint32_t val;

  /* Enable clock to UART peripheral */

  reg = uart->ckenreg;
  val = getreg32(reg);
  val |= uart->ckenbit;
  putreg32(reg, val);

  /* Configure registers for a simple uart, 8 bits, 1 stop bit, no parity */

  //CR1: OVER8=0, UE=1, M=0, WAKE=0, PCE=0, no parity, no interrupts, RE=1, RWU=0
  stm32l4_uart_updatereg(uart, STM32L4_USART_CR1, USART_CR1_UE | USART_CR1_RE | USART_CR1_TE, 0xFFFF4000);

  //CR2: LINEN=0, STOP=00, CLKEN=0, no cpol, no cpha, no lbcl, no lin
  stm32l4_uart_updatereg(uart, STM32L4_USART_CR2, 0, 0xFFFF8090);

  //CR3: ONEBIT=0, no interrupts, CTSE=0, RTSE=0, no dma, SCEN=0, NACK=0, HDSEL=0, no irda
  stm32l4_uart_updatereg(uart, STM32L4_USART_CR3, 0, 0xFFFFF000);

}

/*----------------------------------------------------------------------------*/
/* Disable uart */
static int stm32l4_uart_fini(struct uart_s *uart)
{
  return 0;
}

/*----------------------------------------------------------------------------*/
static inline __attribute__((always_inline)) void send(struct stm32f1_uart_s *dev, uint8_t ch)
{

  /* Wait until the tx buffer is not empty */
  while(!(stm32l4_uart_getreg(uart, STM32L4_USART_ISR) & USART_ISR_TXE));

  /* Send a single byte */
  stm32l4_uart_putreg(uart, STM32L4_USART_TDR, data&0xFF);
}

/*----------------------------------------------------------------------------*/
/* Write some bytes to buffer */
static int stm32l4_uart_write(struct uart_s *uart, const uint8_t *buf, int len)
{
  int i;
  uint8_t ch;

  struct stm32l4_uart_s *dev = (struct stm32l4_uart_s *)uart;

  if (dev->drivemode == DRIVEMODE_BASIC)
    {
      for (i=0; i<len; i++)
        {
          ch = buf[i];
          send(dev, ch);

          if (ch == '\n' && (dev->uart.term.c_oflag & ONLCR))
            {
            send(dev, '\r');
            }

        }
      /* Wait for TC set */
      while ((stm32l4_uart_getreg(dev, STM32F1_USART_SR) & USART_SR_TC) != USART_SR_TC);
      return len;
    } 
 
  return -ENOSYS;
}

/*----------------------------------------------------------------------------*/
/* Finish pending buffer transmission */
static int stm32l4_uart_flush(struct uart_s *uart)
{
  struct stm32l4_uart_s *dev = (struct stm32l4_uart_s *)uart;

  if(dev->drivemode == DRIVEMODE_BASIC)
    {
      return 0;
    }
  
  return -ENOSYS;
}

/*----------------------------------------------------------------------------*/
/* Tell how many bytes can be read */
static int stm32l4_uart_avail(struct uart_s *uart)
{
  struct stm32l4_uart_s *dev = (struct stm32l4_uart_s *)uart;
  
  if(dev->drivemode == DRIVEMODE_BASIC)
    {
      /* Return 1 if RXNE, else zero */
      return 0;
    }
  
  return -ENOSYS;
}

/*----------------------------------------------------------------------------*/
/* Read some bytes from port */
static int stm32f1_uart_read(struct uart_s *uart, uint8_t *buf, int len)
{
  struct stm32l4_uart_s *dev = (struct stm32l4_uart_s *)uart;
  
  if(dev->drivemode == DRIVEMODE_BASIC)
    {
      /* Always read one byte if possible, but never more*/
      return 0;
    }
  
  return -ENOSYS;
}

/*----------------------------------------------------------------------------*/
/* Control port details */
static int stm32l4_uart_ioctl(struct uart_s *uart, int command, void* params)
{
  struct stm32l4_uart_s *dev = (struct stm32l4_uart_s *)uart;
  
  return -ENOSYS;
}

/*----------------------------------------------------------------------------*/
/* This function is called everytime a clock is changed */
static void stm32l4_uart_clockchange(void)
{
  int i;
  /* Clock has changed, recompute baud rates */
  for (i=0; i<STM32L4_UARTCOUNT; i++)
    {
      stm32l4_uart_setbaudrate(g_stm32l4_uarts[i]);
    }
}

/*----------------------------------------------------------------------------*/
/* Low level debug output initialization */
void stm32l4_uart_earlysetup()
{
  int i;

  g_stm32l4_kconsole = NULL;

  /* Register a hook to be notified of clock changes */

  stm32l4_clock_registerhook(stm32l4_uart_clockchange);

  /* Find the kconsole */

  for (i=0; i<STM32FL4_UARTCOUNT; i++)
    {
      if(g_stm32l4_uarts[i]->params->is_kconsole)
        {
          /* Console was found */
          g_stm32l4_kconsole = g_stm32l4_uarts[i];
          g_stm32l4_kconsole->uart.ops->init(&g_stm32l4_kconsole->uart);
          break;
        }
    }

}

/*----------------------------------------------------------------------------*/
static int kputs(const char *data, void *arg)
{
  if(g_stm32l4_kconsole == NULL)
    {
      return 0;
    }

  return g_stm32l4_kconsole->uart.ops->write(&g_stm32l4_kconsole->uart, data, strlen(data));
}

/*----------------------------------------------------------------------------*/
static void kputc(const char data, void *arg)
{
  if(g_stm32l4_kconsole == NULL)
    {
      return;
    }

  g_stm32l4_kconsole->uart.ops->write(&g_stm32l4_kconsole->uart, &data, 1);
}

/*----------------------------------------------------------------------------*/
void stm32l4_uart_send(uint32_t uartid, int data)
{
  const struct stm32l4_uart_s *uart;

}


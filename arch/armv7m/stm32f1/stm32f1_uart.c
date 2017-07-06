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
#include "bits/stm32f1_rcc.h"
#include "bits/stm32f1_gpio.h"
#include "bits/stm32f1_uart.h"
#include "bits/irq.h"
#include "stm32f1_gpio.h"
#include "stm32f1_rcc.h"

/* Possible UART modes:
 *
 * - Normal
 * - Normal/RS-485 with gpio txen
 * - Half-Duplex on TX
 * - Smart Card
 * - LIN
 * - IRDA
 * - Multiprocessor
 * - Synchronous
 * Some helpful details: http://www.micromouseonline.com/2009/12/31/stm32-usart-basics/
 */
 
/*==============================================================================
 * Definitions
 *==============================================================================
 */

#define DRIVEMODE_BASIC 0 /* No interrupt at all, for early boot logs. */
#define DRIVEMODE_IRQ   1 /* IRQ driven tx/rx, still requires CPU for each char, usable when DMA not available. */
#define DRIVEMODE_DMA   2 /* Preprogrammed DMA, does not require CPU for each char. */

#define STOPBITS_0_5     0
#define STOPBITS_1      1
#define STOPBITS_2      2
#define STOPBITS_1_5    3

#define PARITY_NONE     0
#define PARITY_ODD      1
#define PARITY_EVEN     2

/*==============================================================================
 * Types
 *==============================================================================
 */

struct stm32f1_uartparams_s
{
  uint32_t regbase;
  uint32_t rccreg;
  uint32_t rccbit;
  uint32_t remapreg;   /* IO remap register  */
  uint32_t remapmask;  /* IO remap bit mask  */
  uint32_t remapbit;   /* IO remap bit value */
  uint32_t txpin;
  uint32_t rxpin;
  uint8_t  irq;    /* irq line */
  uint8_t  is_kconsole:1; /* set to one if this uart is the kernel console */
};

struct stm32f1_uart_s
{
  struct uart_s                      uart; /* MUST be the first field */
  const struct stm32f1_uartparams_s *params; /*constant values */
  /*other variable values*/
  uint8_t                            drivemode; /* none, irq, dma */
};

/*==============================================================================
 * Function Prototypes
 *==============================================================================
 */

static int stm32f1_uart_init (struct uart_s *uart);
static int stm32f1_uart_fini (struct uart_s *uart);
static int stm32f1_uart_write(struct uart_s *uart, const uint8_t *buf, int len);
static int stm32f1_uart_flush(struct uart_s *uart);
static int stm32f1_uart_avail(struct uart_s *uart);
static int stm32f1_uart_read (struct uart_s *uart, uint8_t *buf, int len);
static int stm32f1_uart_ioctl(struct uart_s *uart, int command, void* params);

static int  kputs(const char *data, void *arg);
static void kputc(const char data, void *arg);

/*==============================================================================
 * Variables and constants
 *==============================================================================
 */

static const struct uart_ops_s g_stm32f1_uartops =
{
  stm32f1_uart_init,
  stm32f1_uart_fini,
  stm32f1_uart_write,
  stm32f1_uart_flush,
  stm32f1_uart_avail,
  stm32f1_uart_read,
  stm32f1_uart_ioctl,
};

#ifdef CONFIG_STM32F1_USART1
static const struct stm32f1_uartparams_s g_stm32f1_usart1params =
{
  .regbase    = STM32F1_REGBASE_USART1,
  .rccreg     = STM32F1_RCC_APB2ENR,
  .rccbit     = RCC_APB2ENR_USART1EN,
  .irq        = STM32F1_IRQ_USART1,
#ifdef CONFIG_STM32F1_USART1_KCONSOLE
  .is_kconsole = 1,
#else
  .is_kconsole = 0,
#endif
  .remapreg   = STM32F1_AFIO_MAPR,
  .remapmask  = AFIO_MAPR_USART1_REMAP,
#ifdef CONFIG_STM32F1_USART1_REMAP
  .remapbit   = AFIO_MAPR_USART1_REMAP,
  .txpin      = GPIO_PORT_B | GPIO_PIN_6 | GPIO_MODE_ALT | GPIO_SPEED_MED | GPIO_TYPE_PP,
  .rxpin      = GPIO_PORT_B | GPIO_PIN_7 | GPIO_MODE_IN  | GPIO_SPEED_MED | GPIO_PULL_UP,
#else
  .remapbit   = 0,
  .txpin      = GPIO_PORT_A | GPIO_PIN_9  | GPIO_MODE_ALT | GPIO_SPEED_MED | GPIO_TYPE_PP,
  .rxpin      = GPIO_PORT_A | GPIO_PIN_10 | GPIO_MODE_IN  | GPIO_SPEED_MED | GPIO_PULL_UP,
#endif
};

static struct stm32f1_uart_s g_stm32f1_usart1 =
{
  .uart =
    {
      .ops          = &g_stm32f1_uartops,

      .term.c_baud  = CONFIG_STM32F1_USART1_BAUDRATE,

#ifdef CONFIG_STM32F1_USART1_KCONSOLE
      .term.c_oflag = ONLCR,
#else
      .term.c_oflag = 0,
#endif

#if defined( CONFIG_STM32F1_USART1_PARITY_NONE )
      .term.c_cflag = 0
#elif defined( CONFIG_STM32F1_USART1_PARITY_ODD )
      .parity   = PARENB | PARODD
#elif defined( CONFIG_STM32F1_USART1_PARITY_EVEN )
      .parity   = PARENB
#else
#error undefined USART1 parity
#endif
#if CONFIG_STM32F1_USART1_STOPBITS == 1
                , /* No additional control flags */
#elif CONFIG_STM32F1_USART1_STOPBITS == 2
                | CSTOPB,
#else
#error unsupported stop bits
#endif
    },

    .params = &g_stm32f1_usart1params,
    .drivemode = DRIVEMODE_BASIC
};
#endif

static struct stm32f1_uart_s * const g_stm32f1_uarts[] = 
{
#ifdef CONFIG_STM32F1_USART1
  &g_stm32f1_usart1
#endif
};

/* Create an enum to count uarts, because sizeof(uarts[0]) will not work if there are no uarts */
enum
{
#ifdef CONFIG_STM32F1_USART1
  STM32F1_INDEX_USART1,
#endif
  STM32F1_UARTCOUNT
};

static struct stm32f1_uart_s *g_stm32f1_kconsole;

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
static inline uint32_t stm32f1_uart_getreg(struct stm32f1_uart_s *uart, int regoff)
{
  return getreg32(uart->params->regbase + regoff);
}

/*----------------------------------------------------------------------------*/
static inline void stm32f1_uart_putreg(struct stm32f1_uart_s *uart, int regoff, uint32_t val)
{
  putreg32(uart->params->regbase + regoff, val);
}

/*----------------------------------------------------------------------------*/
static void stm32f1_uart_setbaudrate(struct stm32f1_uart_s *dev)
{
  uint32_t fclk;
  struct stm32f1_clocks_s * clocks = stm32f1_clock_getinfo();
  if(dev->params->base == STM32F1_REGBASE_USART1)
    {
      fclk = clocks->pclk2;
    }
  else
    {
      fclk = clocks->pclk1;    
    }

  /*                baud = fclk / (16 * usartdiv)
   * Hence 16 * usartdiv = fclk / baud
   * And        usartdiv = fclk / (16 * baud)
   * BUT, this is a 12.4 fixed point number. So BRR must be programmed ito 16x usartdiv
   *            usart_brr = fclk / baud
   */
  stm32f1_uart_putreg(dev, STM32F1_USART_BRR, fclk / dev->uart.term.c_baud);
}

/*----------------------------------------------------------------------------*/
/* Setup baud rate and port params, enable uart */
static int stm32f1_uart_init(struct uart_s *uart)
{
  uint32_t val;
  struct stm32f1_uart_s *dev = (struct stm32f1_uart_s *)uart;
  
  /* Power up device */

  val  = getreg32(STM32F1_REGBASE_RCC + dev->params->rccreg);
  val |= dev->params->rccbit;
  putreg32(STM32F1_REGBASE_RCC + dev->params->rccreg, val);
  
  /* Enable GPIOs and alternate settings */

  stm32f1_gpio_init(dev->params->txpin);
  stm32f1_gpio_init(dev->params->rxpin);
  val  = getreg32(STM32F1_REGBASE_AFIO + dev->params->remapreg);
  val &= ~dev->params->remapmask;
  val |= dev->params->remapbit;
  putreg32(STM32F1_REGBASE_AFIO + dev->params->remapreg, val);

  /* Define port parameters */

  val  = stm32f1_uart_getreg(dev, STM32F1_USART_CR1);
  val &= ~(USART_CR1_RWU | USART_CR1_WAKE);
  val &= ~(USART_CR1_IDLEIE | USART_CR1_RXNEIE |  USART_CR1_TCIE | USART_CR1_TXEIE | USART_CR1_PEIE);
  val |= USART_CR1_RE | USART_CR1_TE;
  
  if (dev->uart.term.c_cflag & PARENB)
    {
      val |= USART_CR1_PCE;
      val |= USART_CR1_M; /* 9-bit frame */
      if (dev->uart.term.c_cflag == PARODD)
        {
          val |= USART_CR1_PS;
        }
      else
        {
          val &= ~USART_CR1_PS;
        }
    }
  else
    {
      val &= ~USART_CR1_PCE;
      val &= ~USART_CR1_M; /* 8-bit frame */
    }
  stm32f1_uart_putreg(dev, STM32F1_USART_CR1, val);

  val  = stm32f1_uart_getreg(dev,STM32F1_USART_CR2);
  val &= ~USART_CR2_ADD_MASK;
  val &= ~(USART_CR2_LBDL | USART_CR2_LBDIE | USART_CR2_LINEN);
  val &= ~(USART_CR2_LBCL | USART_CR2_CPHA | USART_CR2_CPOL | USART_CR2_CLKEN);

  val &= ~USART_CR2_STOP_MASK;
  if (dev->uart.term.c_cflag & CSTOPB)
    {
      val |= USART_CR2_STOP_2;
    }
  else
    {
      val |= USART_CR2_STOP_1;
    }

#if 0
  /* TODO: need an additional term flag for "CSTOPHALF" to remove half a stop bit */
  else if (dev->uart.stopbits==STOPBITS_1_5)
    {
      val |= USART_CR2_STOP_15;
    }
  else if (dev->uart.stopbits==STOPBITS_0_5)
    {
      val |= USART_CR2_STOP_05;
    }
#endif
  
  stm32f1_uart_putreg(dev, STM32F1_USART_CR2, val);
  
  val  = stm32f1_uart_getreg(dev,STM32F1_USART_CR3);
  val &= ~(USART_CR3_EIE | USART_CR3_CTSIE);
  val &= ~(USART_CR3_IREN | USART_CR3_IRLP);
  val &= ~(USART_CR3_HDSEL);
  val &= ~(USART_CR3_NACK | USART_CR3_SCEN);
  val &= ~(USART_CR3_DMAR | USART_CR3_DMAT);
  val &= ~(USART_CR3_RTSE | USART_CR3_CTSE);
  stm32f1_uart_putreg(dev, STM32F1_USART_CR3, val);
  
  stm32f1_uart_setbaudrate(dev);
  
  /* Optionally enable IRQ and DMA */
  
  /* Enable uart */
  val = stm32f1_uart_getreg(dev, STM32F1_USART_CR1);
  val |= USART_CR1_UE;
  stm32f1_uart_putreg(dev, STM32F1_USART_CR1, val);
  
  return 0;
}

/*----------------------------------------------------------------------------*/
/* Disable uart */
static int stm32f1_uart_fini (struct uart_s *uart)
{
  uint32_t val;
  struct stm32f1_uart_s *dev = (struct stm32f1_uart_s *)uart;

  /* Disable uart */
  val = stm32f1_uart_getreg(dev, STM32F1_USART_CR1);
  val &= ~USART_CR1_UE;
  stm32f1_uart_putreg(dev, STM32F1_USART_CR1, val);

  /* Disable IRQ or DMA */

  /* Disable GPIOs */

  stm32f1_gpio_init( (dev->params->txpin & (GPIO_FLAGS_LINE_MASK | GPIO_FLAGS_PORT_MASK)) | GPIO_MODE_IN | GPIO_PULL_NONE);
  stm32f1_gpio_init( (dev->params->rxpin & (GPIO_FLAGS_LINE_MASK | GPIO_FLAGS_LINE_MASK)) | GPIO_MODE_IN | GPIO_PULL_NONE);

  /* Power down device */

  val  = getreg32(STM32F1_REGBASE_RCC + dev->params->rccreg);
  val &= ~dev->params->rccbit;
  putreg32(STM32F1_REGBASE_RCC + dev->params->rccreg, val);

  return 0;
}

/*----------------------------------------------------------------------------*/
static inline __attribute__((always_inline)) void send(struct stm32f1_uart_s *dev, uint8_t ch)
{
  /* Wait for room in the TX buffer (TXE set) */
  while ((stm32f1_uart_getreg(dev, STM32F1_USART_SR) & USART_SR_TXE) != USART_SR_TXE);

  /* Write in the TX buffer */
  stm32f1_uart_putreg(dev, STM32F1_USART_DR, ch);
}

/*----------------------------------------------------------------------------*/
/* Write some bytes to buffer */
static int stm32f1_uart_write(struct uart_s *uart, const uint8_t *buf, int len)
{
  int i;
  uint8_t ch;

  struct stm32f1_uart_s *dev = (struct stm32f1_uart_s *)uart;

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
      while ((stm32f1_uart_getreg(dev, STM32F1_USART_SR) & USART_SR_TC) != USART_SR_TC);
      return len;
    } 
 
  return -ENOSYS;
}

/*----------------------------------------------------------------------------*/
/* Finish pending buffer transmission */
static int stm32f1_uart_flush(struct uart_s *uart)
{
  struct stm32f1_uart_s *dev = (struct stm32f1_uart_s *)uart;

  if(dev->drivemode == DRIVEMODE_BASIC)
    {
      return 0;
    }
  
  return -ENOSYS;
}

/*----------------------------------------------------------------------------*/
/* Tell how many bytes can be read */
static int stm32f1_uart_avail(struct uart_s *uart)
{
  struct stm32f1_uart_s *dev = (struct stm32f1_uart_s *)uart;
  
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
  struct stm32f1_uart_s *dev = (struct stm32f1_uart_s *)uart;
  
  if(dev->drivemode == DRIVEMODE_BASIC)
    {
      /* Always read one byte if possible, but never more*/
      return 0;
    }
  
  return -ENOSYS;
}

/*----------------------------------------------------------------------------*/
/* Control port details */
static int stm32f1_uart_ioctl(struct uart_s *uart, int command, void* params)
{
  struct stm32f1_uart_s *dev = (struct stm32f1_uart_s *)uart;
  
  return -ENOSYS;
}

/*----------------------------------------------------------------------------*/
/* This function is called everytime a clock is changed */
static void stm32f1_uart_clockchange(void)
{
  int i;
  /* Clock has changed, recompute baud rates */
  for (i=0; i<STM32F1_UARTCOUNT; i++)
    {
      stm32f1_uart_setbaudrate(g_stm32f1_uarts[i]);
    }
}

/*----------------------------------------------------------------------------*/
/* Low level debug output initialization */
void stm32f1_uart_earlysetup()
{
  int i;

  g_stm32f1_kconsole = NULL;

  /* Register a hook to be notified of clock changes */

  stm32f1_clock_registerhook(stm32f1_uart_clockchange);

  /* Find the kconsole */

  for (i=0; i<STM32F1_UARTCOUNT; i++)
    {
      if(g_stm32f1_uarts[i]->params->is_kconsole)
        {
          /* Console was found */
          g_stm32f1_kconsole = g_stm32f1_uarts[i];
          g_stm32f1_kconsole->uart.ops->init(&g_stm32f1_kconsole->uart);
          break;
        }
    }

}

/*----------------------------------------------------------------------------*/
static int kputs(const char *data, void *arg)
{
  if(g_stm32f1_kconsole == NULL)
    {
      return 0;
    }

  return g_stm32f1_kconsole->uart.ops->write(&g_stm32f1_kconsole->uart, data, strlen(data));
}

/*----------------------------------------------------------------------------*/
static void kputc(const char data, void *arg)
{
  if(g_stm32f1_kconsole == NULL)
    {
      return;
    }

  g_stm32f1_kconsole->uart.ops->write(&g_stm32f1_kconsole->uart, &data, 1);
}


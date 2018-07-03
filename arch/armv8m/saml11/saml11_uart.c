#include "config.h"

#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <termios.h>
#include <slos/uart.h>
#include <slos/stdio.h>

#include "armv8m.h"
#include "bits/saml11_periphs.h"
#include "bits/saml11_gpiobits.h"
#include "bits/saml11_uartbits.h"
#include "bits/irq.h"
#include "saml11_gpio.h"
#include "saml11_clock.h"
#include "saml11_uart.h"

/*==============================================================================
 * Definitions
 *==============================================================================
 */

#define DRIVEMODE_BASIC 0 /* No interrupt at all, for early boot logs. */
#define DRIVEMODE_IRQ   1 /* IRQ driven tx/rx, still requires CPU for each char, usable when DMA not available. */
#define DRIVEMODE_DMA   2 /* Preprogrammed DMA, does not require CPU for each char. */

#define STOPBITS_0_5    0
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

struct saml11_uartparams_s
{
  uint32_t base;
  uint32_t ckenreg;
  uint32_t ckenbit;
  uint32_t txpin;
  uint32_t rxpin;
  uint8_t  irq;    /* irq line */
  uint8_t  is_kconsole:1; /* set to one if this uart is the kernel console */
};

struct saml11_uart_s
{
  struct uart_s                     uart; /* MUST be the first field */
  const struct saml11_uartparams_s *params; /*constant values */
  /*other variable values*/
  uint8_t                           drivemode; /* none, irq, dma */
};

/*==============================================================================
 * Function Prototypes
 *==============================================================================
 */

static int saml11_uart_init (struct uart_s *uart);
static int saml11_uart_fini (struct uart_s *uart);
static int saml11_uart_write(struct uart_s *uart, const uint8_t *buf, int len);
static int saml11_uart_flush(struct uart_s *uart);
static int saml11_uart_avail(struct uart_s *uart);
static int saml11_uart_read (struct uart_s *uart, uint8_t *buf, int len);
static int saml11_uart_ioctl(struct uart_s *uart, int command, void* params);

static int  kputs(const char *data, void *arg);
static void kputc(const char data, void *arg);

/*==============================================================================
 * Variables and constants
 *==============================================================================
 */

static const struct uart_ops_s g_saml11_uartops =
{
  .init  = saml11_uart_init,
  .fini  = saml11_uart_fini,
  .write = saml11_uart_write,
  .flush = saml11_uart_flush,
  .avail = saml11_uart_avail,
  .read  = saml11_uart_read,
  .ioctl = saml11_uart_ioctl,
};

static struct saml11_uart_s *g_saml11_kconsole;

/* Stream structure used by the kprintf function in libc */
const struct printf_stream_s konsole =
{
  .putchar = kputc,
  .puts    = kputs
};

#ifdef CONFIG_SAML11_SERCOM0UART
static const struct saml11_uartparams_s g_saml11_sercom0uartparams =
{
  .base       = SAML11_REGBASE_SERCOM0UART,
  .ckenreg    = SAML11_RCC_APB2ENR,
  .ckenbit    = RCC_APB2ENR_SERCOM0UARTEN,

  .irq        = SAML11_IRQ_SERCOM0UART,
#ifdef CONFIG_SAML11_SERCOM0UART_KCONSOLE
  .is_kconsole = 1,
#else
  .is_kconsole = 0,
#endif
#if defined( CONFIG_SAML11_SERCOM0UART_TX_NONE)
  .txpin      = 0,
#elif defined( CONFIG_SAML11_SERCOM0UART_TX_A9)
  .txpin      = GPIO_PORT_A | GPIO_PIN_9 | GPIO_MODE_ALT | GPIO_ALT_7,
#elif defined( CONFIG_SAML11_SERCOM0UART_TX_B6)
  .txpin      = GPIO_PORT_B | GPIO_PIN_6 | GPIO_MODE_ALT | GPIO_ALT_7,
#else
#error invalid usart1 tx config
#endif
#if defined( CONFIG_SAML11_SERCOM0UART_RX_NONE)
  .rxpin      = 0,
#elif defined( CONFIG_SAML11_SERCOM0UART_RX_A10)
  .rxpin      = GPIO_PORT_A | GPIO_PIN_10 | GPIO_MODE_ALT | GPIO_ALT_7,
#elif defined( CONFIG_SAML11_SERCOM0UART_RX_B7)
  .rxpin      = GPIO_PORT_B | GPIO_PIN_7 | GPIO_MODE_ALT | GPIO_ALT_7,
#else
#error invalid usart1 rx config
#endif
};

static struct saml11_uart_s g_saml11_sercom0uart =
{
  .uart =
    {
      .ops          = &g_saml11_uartops,

      .term.c_baud  = CONFIG_SAML11_SERCOM0UART_BAUDRATE,

#ifdef CONFIG_SAML11_SERCOM0UART_KCONSOLE
      .term.c_oflag = ONLCR,
#else
      .term.c_oflag = 0,
#endif

#if defined( CONFIG_SAML11_SERCOM0UART_PARITY_NONE )
      .term.c_cflag = 0
#elif defined( CONFIG_SAML11_SERCOM0UART_PARITY_ODD )
      .parity   = PARENB | PARODD
#elif defined( CONFIG_SAML11_SERCOM0UART_PARITY_EVEN )
      .parity   = PARENB
#else
#error undefined USART1 parity
#endif
#if CONFIG_SAML11_SERCOM0UART_STOPBITS == 1
                , /* No additional control flags */
#elif CONFIG_SAML11_SERCOM0UART_STOPBITS == 2
                | CSTOPB,
#else
#error unsupported stop bits
#endif
    },

    .params = &g_saml11_sercom0uartparams,
    .drivemode = DRIVEMODE_BASIC
};
#endif

#ifdef CONFIG_SAML11_SERCOM1UART
static const struct saml11_uartparams_s g_saml11_sercom1uartparams =
{
  .base       = SAML11_REGBASE_SERCOM1UART,
  .ckenreg    = SAML11_RCC_APB1ENR1,
  .ckenbit    = RCC_APB1ENR1_SERCOM1UARTEN,

  .irq        = SAML11_IRQ_SERCOM1UART,
#ifdef CONFIG_SAML11_SERCOM1UART_KCONSOLE
  .is_kconsole = 1,
#else
  .is_kconsole = 0,
#endif
#if defined( CONFIG_SAML11_SERCOM1UART_TX_NONE)
  .txpin      = 0,
#elif defined( CONFIG_SAML11_SERCOM1UART_TX_A2)
  .txpin      = GPIO_PORT_A | GPIO_PIN_2 | GPIO_MODE_ALT | GPIO_ALT_7,
#elif defined( CONFIG_SAML11_SERCOM1UART_TX_D5)
  .txpin      = GPIO_PORT_D | GPIO_PIN_5 | GPIO_MODE_ALT | GPIO_ALT_7,
#else
#error invalid usart2 tx config
#endif
#if defined( CONFIG_SAML11_SERCOM1UART_RX_NONE)
  .rxpin      = 0,
#elif defined( CONFIG_SAML11_SERCOM1UART_RX_A3)
  .rxpin      = GPIO_PORT_A | GPIO_PIN_3 | GPIO_MODE_ALT | GPIO_ALT_7,
#elif defined( CONFIG_SAML11_SERCOM1UART_RX_A15)
  .rxpin      = GPIO_PORT_A | GPIO_PIN_15 | GPIO_MODE_ALT | GPIO_ALT_3,
#elif defined( CONFIG_SAML11_SERCOM1UART_RX_D6)
  .rxpin      = GPIO_PORT_D | GPIO_PIN_6 | GPIO_MODE_ALT | GPIO_ALT_7,
#else
#error invalid usart2 rx config
#endif
};

static struct saml11_uart_s g_saml11_sercom1uart =
{
  .uart =
    {
      .ops          = &g_saml11_uartops,

      .term.c_baud  = CONFIG_SAML11_SERCOM1UART_BAUDRATE,

#ifdef CONFIG_SAML11_SERCOM1UART_KCONSOLE
      .term.c_oflag = ONLCR,
#else
      .term.c_oflag = 0,
#endif

#if defined( CONFIG_SAML11_SERCOM1UART_PARITY_NONE )
      .term.c_cflag = 0
#elif defined( CONFIG_SAML11_SERCOM1UART_PARITY_ODD )
      .parity   = PARENB | PARODD
#elif defined( CONFIG_SAML11_SERCOM1UART_PARITY_EVEN )
      .parity   = PARENB
#else
#error undefined USART2 parity
#endif
#if CONFIG_SAML11_SERCOM1UART_STOPBITS == 1
                , /* No additional control flags */
#elif CONFIG_SAML11_SERCOM1UART_STOPBITS == 2
                | CSTOPB,
#else
#error unsupported stop bits
#endif
    },

    .params = &g_saml11_sercom1uartparams,
    .drivemode = DRIVEMODE_BASIC
};
#endif

static struct saml11_uart_s * g_saml11_uarts[] = {
#ifdef CONFIG_SAML11_SERCOM0UART
  &g_saml11_sercom0uart,
#endif
#ifdef CONFIG_SAML11_SERCOM1UART
  &g_saml11_sercom1uart,
#endif
#ifdef CONFIG_SAML11_SERCOM2UART
  &g_saml11_sercom2uart,
#endif
};

/* Create an enum to count uarts, because sizeof(uarts[0]) will not work if there are no uarts */
enum
{
#ifdef CONFIG_SAML11_SERCOM0UART
  SAML11_INDEX_SERCOM0UART,
#endif
#ifdef CONFIG_SAML11_SERCOM1UART
  SAML11_INDEX_SERCOM1UART,
#endif
#ifdef CONFIG_SAML11_SERCOM2UART
  SAML11_INDEX_SERCOM2UART,
#endif
  SAML11_UARTCOUNT
};

/*==============================================================================
 * Functions
 *==============================================================================
 */

/*----------------------------------------------------------------------------*/
static inline uint32_t saml11_uart_getreg(const struct saml11_uart_s *uart, uint32_t regoff)
{
  return getreg32(uart->params->base + regoff);
}

/*----------------------------------------------------------------------------*/
static inline void saml11_uart_putreg(const struct saml11_uart_s *uart, uint32_t regoff, uint32_t value)
{
  putreg32(uart->params->base + regoff, value);
}

/*----------------------------------------------------------------------------*/
static inline void saml11_uart_updatereg(const struct saml11_uart_s *uart, uint32_t regoff, uint32_t setbits, uint32_t clrbits)
{
  updatereg32(uart->params->base + regoff, setbits, clrbits);
}

/*----------------------------------------------------------------------------*/
/*
 * Fclk      baud      float     int(16times) hex   int part   frac part      approximated
 * 16 MHz    115200    8,68055   138          0x8A  8          10/16 = 0.625  8.625
 */
static void saml11_uart_setbaudrate(struct saml11_uart_s *uart)
{
  struct saml11_clocks_s *infos;
  struct saml11_uart_s *dev = (struct saml11_uart_s*)uart;
  uint32_t clock,baud;

  infos = saml11_clock_getinfo();

  if(dev->params->base == SAML11_REGBASE_SERCOM0UART)
    {
      clock = infos->pclk2;
    }
  else
    {
      clock = infos->pclk1;
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
  baud = clock / uart->uart.term.c_baud;

  /* Set */
  saml11_uart_putreg(uart, SAML11_USART_BRR, baud & 0xFFFF);
}

/*----------------------------------------------------------------------------*/
static int saml11_uart_init(struct uart_s *uart)
{
#if 0
  uint32_t val;

  struct saml11_uart_s * dev = (struct saml11_uart_s*)uart;

  /* Enable clock to UART peripheral */

  updatereg32(SAML11_REGBASE_RCC + dev->params->ckenreg, dev->params->ckenbit, 0);

  /* Configure registers for a simple rs232 uart */
  val = saml11_uart_getreg(dev, SAML11_USART_CR1);

  /* Configure GPIOs */
  if (dev->params->rxpin)
    {
      saml11_gpio_init(dev->params->rxpin);
      val |= USART_CR1_RE;
    }
  if (dev->params->txpin)
    {
      saml11_gpio_init(dev->params->txpin);
      val |= USART_CR1_TE;
    }


  val &= ~(USART_CR1_M1 | USART_CR1_OVER8 | USART_CR1_MME | USART_CR1_WAKE | USART_CR1_UESM);
  val &= ~(USART_CR1_EOBIE | USART_CR1_RTOIE | USART_CR1_CMIE | USART_CR1_PEIE | USART_CR1_TXEIE | USART_CR1_TCIE | \
           USART_CR1_RXNEIE | USART_CR1_IDLEIE);


  if (dev->uart.term.c_cflag & PARENB)
    {
      val |=  USART_CR1_PCE;
      val |=  USART_CR1_M0; /* 9-bit frame */
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
      val &= ~USART_CR1_M0; /* 8-bit frame */
    }

  saml11_uart_putreg(dev, SAML11_USART_CR1, val);

  val = saml11_uart_getreg(dev, SAML11_USART_CR2);

  val &= ~(USART_CR2_ADD_MASK | USART_CR2_RTOEN | USART_CR2_ABRMOD_MASK | USART_CR2_ABREN | USART_CR2_MSBFIRST | \
           USART_CR2_DATAINV | USART_CR2_TXINV | USART_CR2_RXINV | USART_CR2_SWAP | USART_CR2_LINEN | USART_CR2_CLKEN | \
           USART_CR2_CPOL | USART_CR2_CPHA | USART_CR2_LBCL | USART_CR2_LBDIE | USART_CR2_LBDL | USART_CR2_ADDM7);

  val &= USART_CR2_STOP_MASK;
  if (dev->uart.term.c_cflag & CSTOPB)
    {
      val |= USART_CR2_STOP_2;
    }
  else
    {
      val |= USART_CR2_STOP_1;
    }

  saml11_uart_putreg(dev, SAML11_USART_CR2, val);

  val = saml11_uart_getreg(dev, SAML11_USART_CR3);
  val &= ~(USART_CR3_UCESM | USART_CR3_WUS_MASK | USART_CR3_SCARCNT_MASK | USART_CR3_DEP | USART_CR3_DEM | \
           USART_CR3_OVRDIS | USART_CR3_ONEBIT | USART_CR3_CTSE | USART_CR3_RTSE | USART_CR3_SCEN | \
           USART_CR3_NACK | USART_CR3_HDSEL |USART_CR3_IRLP | USART_CR3_IREN);
  val &= ~(USART_CR3_TCBGTIE | USART_CR3_WUFIE | USART_CR3_CTSIE | USART_CR3_EIE);
  val &= ~(USART_CR3_DDRE | USART_CR3_DMAT | USART_CR3_DMAR);

  saml11_uart_putreg(dev, SAML11_USART_CR3, val);

  saml11_uart_setbaudrate(dev);

  /* Optionally enable IRQ and DMA */

  /* Enable UART */

  saml11_uart_updatereg(dev, SAML11_USART_CR1, USART_CR1_UE, 0);
#else
#warning TODO
#endif
  return 0;
}

/*----------------------------------------------------------------------------*/
/* Disable uart */
static int saml11_uart_fini(struct uart_s *uart)
{
  return 0;
}

/*----------------------------------------------------------------------------*/
static inline __attribute__((always_inline)) void send(struct saml11_uart_s *dev, uint8_t ch)
{
#if 0
  /* Wait until the tx buffer is not empty */
  while(!(saml11_uart_getreg(dev, SAML11_USART_ISR) & USART_ISR_TXE));

  /* Send a single byte */
  saml11_uart_putreg(dev, SAML11_USART_TDR, ch);
#endif
}

/*----------------------------------------------------------------------------*/
/* Write some bytes to buffer */
static int saml11_uart_write(struct uart_s *uart, const uint8_t *buf, int len)
{
#if 0
  int i;
  uint8_t ch;

  struct saml11_uart_s *dev = (struct saml11_uart_s *)uart;

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
      while ((saml11_uart_getreg(dev, SAML11_USART_ISR) & USART_ISR_TC) != USART_ISR_TC);
      return len;
    } 
#endif
  return -ENOSYS;
}

/*----------------------------------------------------------------------------*/
/* Finish pending buffer transmission */
static int saml11_uart_flush(struct uart_s *uart)
{
  struct saml11_uart_s *dev = (struct saml11_uart_s *)uart;

  if(dev->drivemode == DRIVEMODE_BASIC)
    {
      return 0;
    }
  
  return -ENOSYS;
}

/*----------------------------------------------------------------------------*/
/* Tell how many bytes can be read */
static int saml11_uart_avail(struct uart_s *uart)
{
  struct saml11_uart_s *dev = (struct saml11_uart_s *)uart;
  
  if(dev->drivemode == DRIVEMODE_BASIC)
    {
      /* Return 1 if RXNE, else zero */
      return 0;
    }
  
  return -ENOSYS;
}

/*----------------------------------------------------------------------------*/
/* Read some bytes from port */
static int saml11_uart_read(struct uart_s *uart, uint8_t *buf, int len)
{
  struct saml11_uart_s *dev = (struct saml11_uart_s *)uart;
  
  if(dev->drivemode == DRIVEMODE_BASIC)
    {
      /* Always read one byte if possible, but never more*/
      return 0;
    }
  
  return -ENOSYS;
}

/*----------------------------------------------------------------------------*/
/* Control port details */
static int saml11_uart_ioctl(struct uart_s *uart, int command, void* params)
{
  //struct saml11_uart_s *dev = (struct saml11_uart_s *)uart;
  
  return -ENOSYS;
}

/*----------------------------------------------------------------------------*/
/* This function is called everytime a clock is changed */
static void saml11_uart_clockchange(void)
{
  int i;
  /* Clock has changed, recompute baud rates */
  for (i=0; i<SAML11_UARTCOUNT; i++)
    {
      saml11_uart_setbaudrate(g_saml11_uarts[i]);
    }
}

/*----------------------------------------------------------------------------*/
/* Low level debug output initialization */
void saml11_uart_earlysetup()
{
  int i;

  g_saml11_kconsole = NULL;

  /* Register a hook to be notified of clock changes */

  saml11_clock_registerhook(saml11_uart_clockchange);

  /* Find the kconsole */

  for (i=0; i<SAML11_UARTCOUNT; i++)
    {
      if(g_saml11_uarts[i]->params->is_kconsole)
        {
          /* Console was found */
          g_saml11_kconsole = g_saml11_uarts[i];
          g_saml11_kconsole->uart.ops->init(&g_saml11_kconsole->uart);
          break;
        }
    }

}

/*----------------------------------------------------------------------------*/
static int kputs(const char *data, void *arg)
{
  if(g_saml11_kconsole == NULL)
    {
      return 0;
    }

  return g_saml11_kconsole->uart.ops->write(&g_saml11_kconsole->uart, (const uint8_t*)data, strlen(data));
}

/*----------------------------------------------------------------------------*/
static void kputc(const char data, void *arg)
{
  if(g_saml11_kconsole == NULL)
    {
      return;
    }

  g_saml11_kconsole->uart.ops->write(&g_saml11_kconsole->uart, (const uint8_t*)&data, 1);
}


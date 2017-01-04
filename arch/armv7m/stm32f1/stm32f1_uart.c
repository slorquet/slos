#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <slos/uart.h>
#include <slos/stdio.h>

#include "armv7m.h"
#include "bits/stm32f1_periphs.h"
#include "bits/stm32f1_rcc.h"
#include "bits/stm32f1_gpio.h"
#include "bits/irq.h"
#include "stm32f1_gpio.h"

/*==============================================================================
 * Definitions
 *==============================================================================
 */

#define DRIVEMODE_BASIC 0 /* No interrupt at all, for early boot logs. */
#define DRIVEMODE_IRQ   1 /* IRQ driven tx/rx, still requires CPU for each char, usable when DMA not available. */
#define DRIVEMODE_DMA   2 /* Preprogrammed DMA, does not require CPU for each char. */

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

static void kputs(const char *data, void *arg);
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
      .ops = &g_stm32f1_uartops,
      .baudrate = CONFIG_STM32F1_USART1_BAUDRATE,
#if defined( CONFIG_STM32F1_USART1_PARITY_NONE )
      .parity   = 0,
#elif defined( CONFIG_STM32F1_USART1_PARITY_ODD )
      .parity   = 1,
#elif defined( CONFIG_STM32F1_USART1_PARITY_EVEN )
      .parity   = 2,
#else
#error undefined USART1 parity
#endif
      .databits = CONFIG_STM32F1_USART1_DATABITS,
      .stopbits = CONFIG_STM32F1_USART1_STOPBITS,
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
/*setup baud rate and port params, enable uart*/
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
  
  /* Optionally enable IRQ and DMA */
  
  /* Enable uart */
  
  return -ENOSYS;
}

/*----------------------------------------------------------------------------*/
/*disable uart*/
static int stm32f1_uart_fini (struct uart_s *uart)
{
  uint32_t val;
  struct stm32f1_uart_s *dev = (struct stm32f1_uart_s *)uart;

  /* Disable uart */

  /* Disable IRQ or DMA */

  /* Disable GPIOs */
  stm32f1_gpio_init( (dev->params->txpin & (GPIO_FLAGS_LINE_MASK | GPIO_FLAGS_PORT_MASK)) | GPIO_MODE_IN | GPIO_PULL_NONE);
  stm32f1_gpio_init( (dev->params->rxpin & (GPIO_FLAGS_LINE_MASK | GPIO_FLAGS_LINE_MASK)) | GPIO_MODE_IN | GPIO_PULL_NONE);

  /* Power down device */

  val  = getreg32(STM32F1_REGBASE_RCC + dev->params->rccreg);
  val &= ~dev->params->rccbit;
  putreg32(STM32F1_REGBASE_RCC + dev->params->rccreg, val);

  return -ENOSYS;
}

/*----------------------------------------------------------------------------*/
/*write some bytes to buffer*/
static int stm32f1_uart_write(struct uart_s *uart, const uint8_t *buf, int len)
{
  int i;

  struct stm32f1_uart_s *dev = (struct stm32f1_uart_s *)uart;

  if(dev->drivemode == DRIVEMODE_BASIC)
    {
      for(i=0; i<len; i++)
        {
          /* Wait for TXE set */
          /* Write TX data reg */
        }
      return len;
    } 
 
  return -ENOSYS;
}

/*----------------------------------------------------------------------------*/
/*finish buffer transmission*/
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
/*tell how many bytes can be read*/
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
/*read some bytes from port*/
static int stm32f1_uart_read (struct uart_s *uart, uint8_t *buf, int len)
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
/*control port details*/
static int stm32f1_uart_ioctl(struct uart_s *uart, int command, void* params)
{
  struct stm32f1_uart_s *dev = (struct stm32f1_uart_s *)uart;
  
  return -ENOSYS;
}

/*----------------------------------------------------------------------------*/
/* Low level debug output initialization */
void stm32f1_uart_earlysetup()
{
  int i;

  g_stm32f1_kconsole = NULL;

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
static void kputs(const char *data, void *arg)
{
  if(g_stm32f1_kconsole == NULL)
    {
      return;
    }

  g_stm32f1_kconsole->uart.ops->write(&g_stm32f1_kconsole->uart, data, strlen(data));
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


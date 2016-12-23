#include <stdint.h>
#include <errno.h>
#include <slos/uart.h>

#include "bits/stm32f1_periphs.h"
#include "bits/stm32f1_rcc.h"
#include "bits/irq.h"

struct stm32f1_uartparams_s
{
  uint32_t regbase;
  uint32_t rccreg;
  uint32_t rccbit;
  uint8_t  irq;    /* irq line */
};

struct stm32f1_uart_s
{
  struct uart_s                      uart; /* MUST be the first field */
  const struct stm32f1_uartparams_s *params; /*constant values */
  /*other variable values*/
  uint8_t                            drivemode; /* none, irq, dma */
};

static int stm32f1_uart_init (struct uart_s *uart);
static int stm32f1_uart_fini (struct uart_s *uart);
static int stm32f1_uart_write(struct uart_s *uart, const uint8_t *buf, int len);
static int stm32f1_uart_flush(struct uart_s *uart);
static int stm32f1_uart_avail(struct uart_s *uart);
static int stm32f1_uart_read (struct uart_s *uart, uint8_t *buf, int len);
static int stm32f1_uart_ioctl(struct uart_s *uart, int command, void* params);

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
  .irq        = STM32F1_IRQ_USART1
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
    .drivemode = 0
};
#endif

/*----------------------------------------------------------------------------*/
/*setup baud rate and port params, enable uart*/
static int stm32f1_uart_init(struct uart_s *uart)
{
  struct stm32f1_uart_s *dev = (struct stm32f1_uart_s *)uart;
  
  /* Power up uart */
  
  /* Define port parameters */
  
  /* Enable GPIOs */
  
  /* Optionnally enable IRQ and DMA */
  
  /* Enable uart */
  
  return -ENOSYS;
}

/*----------------------------------------------------------------------------*/
/*disable uart*/
static int stm32f1_uart_fini (struct uart_s *uart)
{
  struct stm32f1_uart_s *dev = (struct stm32f1_uart_s *)uart;
  
  return -ENOSYS;
}

/*----------------------------------------------------------------------------*/
/*write some bytes to buffer*/
static int stm32f1_uart_write(struct uart_s *uart, const uint8_t *buf, int len)
{
  struct stm32f1_uart_s *dev = (struct stm32f1_uart_s *)uart;
  
  return -ENOSYS;
}

/*----------------------------------------------------------------------------*/
/*finish buffer transmission*/
static int stm32f1_uart_flush(struct uart_s *uart)
{
  struct stm32f1_uart_s *dev = (struct stm32f1_uart_s *)uart;
  
  return -ENOSYS;
}

/*----------------------------------------------------------------------------*/
/*tell how many bytes can be read*/
static int stm32f1_uart_avail(struct uart_s *uart)
{
  struct stm32f1_uart_s *dev = (struct stm32f1_uart_s *)uart;
  
  return -ENOSYS;
}

/*----------------------------------------------------------------------------*/
/*read some bytes from port*/
static int stm32f1_uart_read (struct uart_s *uart, uint8_t *buf, int len)
{
  struct stm32f1_uart_s *dev = (struct stm32f1_uart_s *)uart;
  
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
void stm32f1_uart_earlysetup()
{
  g_stm32f1_usart1.uart.ops->init(&g_stm32f1_usart1.uart);
}


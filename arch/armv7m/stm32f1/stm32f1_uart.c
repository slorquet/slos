#include <stdint.h>
#include <errno.h>
#include <slos/uart.h>

#include "bits/stm32f1_periphs.h"
#include "bits/stm32f1_rcc.h"

static int stm32f1_uart_init (struct uart_s *uart);
static int stm32f1_uart_fini (struct uart_s *uart);
static int stm32f1_uart_write(struct uart_s *uart, uint8_t *buf, int len);
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

struct stm32f1_uart_s
{
  struct uart_s uart;
  uint32_t regbase;
  uint32_t rccreg;
  uint32_t rccbitmask;
};

static const struct stm32f1_uart_s g_stm32f1_usart1 =
{
  .uart =
    {
      .ops = &g_stm32f1_uartops,
    },
  .regbase    = STM32F1_REGBASE_USART1,
  .rccreg     = STM32F1_RCC_APB2ENR,
  .rccbitmask = RCC_APB2ENR_USART1EN,
};

/*----------------------------------------------------------------------------*/
/*setup baud rate and port params, enable uart*/
static int stm32f1_uart_init(struct uart_s *uart)
{
  return -ENOSYS;
}

/*----------------------------------------------------------------------------*/
/*disable uart*/
static int stm32f1_uart_fini (struct uart_s *uart)
{
  return -ENOSYS;
}

/*----------------------------------------------------------------------------*/
/*write some bytes to buffer*/
static int stm32f1_uart_write(struct uart_s *uart, uint8_t *buf, int len)
{
  return -ENOSYS;
}

/*----------------------------------------------------------------------------*/
/*finish buffer transmission*/
static int stm32f1_uart_flush(struct uart_s *uart)
{
  return -ENOSYS;
}

/*----------------------------------------------------------------------------*/
/*tell how many bytes can be read*/
static int stm32f1_uart_avail(struct uart_s *uart)
{
  return -ENOSYS;
}

/*----------------------------------------------------------------------------*/
/*read some bytes from port*/
static int stm32f1_uart_read (struct uart_s *uart, uint8_t *buf, int len)
{
  return -ENOSYS;
}

/*----------------------------------------------------------------------------*/
/*control port details*/
static int stm32f1_uart_ioctl(struct uart_s *uart, int command, void* params)
{
  return -ENOSYS;
}

/*----------------------------------------------------------------------------*/
void stm32f1_uart_earlysetup()
{
  g_stm32f1_usart1.uart.ops->init(&g_stm32f1_usart1);
}


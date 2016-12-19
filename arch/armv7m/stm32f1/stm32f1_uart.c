#include <stdint.h>

struct stm32f1_uart_s
{
  uint32_t regbase;
  uint32_t rccreg;
  uint32_t rccbitmask;
};

static const struct stm32f1_uart_s g_usart1 =
{
  .regbase = 
};

void stm32f1_uart_earlysetup(void)
{
}


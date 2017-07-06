#include <config.h>

#include "stm32l4_rcc.h"
#include "stm32l4_uart.h"

void chip_start(void)
{
  stm32l4_clock_setup();

  stm32l4_uart_earlysetup();
}


#include "stm32f1_rcc.h"
#include "stm32f1_uart.h"

void chip_start(void)
{
  stm32f1_clock_setup();

  stm32f1_rcc_enableperipherals();

  stm32f1_uart_earlysetup();
}


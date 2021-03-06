#include <config.h>

#include "stm32l4_rcc.h"
#include "stm32l4_uart.h"
#include "stm32l4_flash.h"

void chip_start(void)
{
  stm32l4_clock_setup();

  stm32l4_uart_earlysetup();

#ifdef CONFIG_STM32L4_FLASH
  stm32l4_flash_init();
#endif

}


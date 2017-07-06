#include <stdint.h>
#include <slos/stdio.h>

#include "armv7m_systick.h"
#include "armv7m_nvic.h"

#include "stm32l4_rcc.h"
#include "stm32l4_gpio.h"
#include "stm32l4_uart.h"
#include "stm32l4_spi.h"

/* nucleo led on arduino D13 (PB3) */
#define LED (GPIO_PORT_B | GPIO_PIN_3)

void board_start(void)
{
  uint32_t state = 0;
  uint32_t i;

  stm32l4_gpio_init(LED | GPIO_MODE_OUT | GPIO_PULL_UP | GPIO_TYPE_PP ); /*LED PIN ON A5*/

  /*write something*/
  kprintf("Hello L432KC\n");
	
  /*switch the LED on (it's on PA5)*/
  /* Loop blinking led */

  armv7m_systick_init();

  armv7m_irq_enable();

  while(1)
    {
      stm32l4_gpio_write(LED, state);
      state = !state;
      for(i=0;i<100000;i++) {};
    }
	
}

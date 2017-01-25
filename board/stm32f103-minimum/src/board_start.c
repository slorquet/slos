#include <stdint.h>

#include "stm32f1_rcc.h"
#include "stm32f1_gpio.h"
#include "stm32f1_uart.h"

#define PC13 (GPIO_PORT_C | GPIO_PIN_13)

void board_start(void)
{
  uint32_t state = 1;
  volatile int i;

  /* configure pc13 as output to blink the led */
  stm32f1_gpio_init(PC13 | GPIO_MODE_OUT | GPIO_TYPE_PP | GPIO_SPEED_LOW | GPIO_STATE_CLEAR);

  /* Test UART */
  kprintf("Hello world!\n");

  /* Loop blinking led */

  while(1)
    {
      stm32f1_gpio_write(PC13, state);
      state = !state;
      for(i=0;i<100000;i++) {};
    }
}

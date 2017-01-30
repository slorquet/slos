#include <stdint.h>

#include "irq.h"

#include "stm32f1_rcc.h"
#include "stm32f1_gpio.h"
#include "stm32f1_uart.h"
#include "stm32f1_rtc.h"
#include <slos/stdio.h>

#define PC13 (GPIO_PORT_C | GPIO_PIN_13)

void board_start(void)
{
  uint32_t state = 1;
  volatile int i;
  bool succ;

  /* configure pc13 as output to blink the led */
  stm32f1_gpio_init(PC13 | GPIO_MODE_OUT | GPIO_TYPE_PP | GPIO_SPEED_LOW | GPIO_STATE_CLEAR);

  /* Test UART */
  kprintf("Hello %s!\n\n", "world");
  kprintf("hex   = %x\n", 0xA42B);
  kprintf("HEX   = %X\n", 0xA42B);
  kprintf("sdecp = %d\n", 12345);
  kprintf("sdecp = %d\n", 42);
  kprintf("snegn = %d\n", -42);
  kprintf("udecp = %u\n", 42);
  kprintf("unegn = %u\n", -42);
  kprintf("ptr   = %p\n", &state);

  kprintf("Enable LSE\n");
  succ = stm32f1_clock_lse_enable(true);
  kprintf("LSE status %s\n",succ?"OK":"Fail");

  succ = stm32f1_clock_rtc(RTC_SRC_LSE);
  kprintf("LSE to RTC %s\n",succ?"OK":"Fail");

  succ = stm32f1_rtc_init(32767);
  kprintf("RTC init %s\n",succ?"OK":"Fail");

  armv7m_irq_enable();

  /* Loop blinking led */

  while(1)
    {
      stm32f1_gpio_write(PC13, state);
      state = !state;
      for(i=0;i<100000;i++) {};
      kprintf("RTC=%d\n", stm32f1_rtc_read() );
    }
}

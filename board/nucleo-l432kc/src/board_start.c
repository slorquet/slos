#include <stdint.h>
#include <stddef.h>
#include <slos/stdio.h>

#include "armv7m_systick.h"
#include "armv7m_nvic.h"

#include "stm32l4_rcc.h"
#include "stm32l4_gpio.h"
#include "stm32l4_uart.h"
#include "stm32l4_spi.h"
#include "stm32l4_flash.h"

/*==============================================================================
 * Definitions
 *==============================================================================
 */

/* nucleo led on arduino D13 (PB3) */
#define LED (GPIO_PORT_B | GPIO_PIN_3)

/*==============================================================================
 * Variables and constants
 *==============================================================================
 */
static uint32_t ctr;
extern uint32_t *_userflash_start;

/*==============================================================================
 * Functions
 *==============================================================================
 */

/*----------------------------------------------------------------------------*/
void systick_irq(uint32_t irqno, void **context, void *arg)
{
  ctr++;

  if( (ctr % 1000)==0)
    kprintf("systick!\n");
}

/*----------------------------------------------------------------------------*/
void board_start(void)
{
  struct stm32l4_devicesig_s sig;
  uint32_t start;

  stm32l4_gpio_init(LED | GPIO_MODE_OUT | GPIO_PULL_UP | GPIO_TYPE_PP ); /*LED PIN ON A5*/

  /*write something*/
  kprintf("Hello L432KC\n");

  stm32l4_flash_getdevicesig(&sig);
  kprintf("Wafer #%d X=%d Y=%d\n",sig.waf_num,sig.waf_x,sig.waf_y);
  kprintf("Lot num: [%s]\n", sig.lotnum);
  kprintf("package: %d, Flash size %dKB\n",sig.package, sig.flashsize);

  start = (uint32_t)&_userflash_start;
  kprintf("Erasing the rest of flash, start addr=0x%x\n", start);

  armv7m_systick_callback(systick_irq, NULL);
}

/*----------------------------------------------------------------------------*/
void board_main(void)
{
  uint32_t i;
  uint32_t state = 0;
  /* Loop blinking led */

  while(1)
    {
      stm32l4_gpio_write(LED, state);
      state = !state;
      for(i=0;i<100000;i++) {};
    }
}


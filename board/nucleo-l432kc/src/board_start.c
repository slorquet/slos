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

#include <slos/mm/mm.h>

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

struct heap_s heap;
uint8_t heap_data[1000];

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

  stm32l4_gpio_init(LED | GPIO_MODE_OUT | GPIO_PULL_UP | GPIO_TYPE_PP ); /*LED PIN ON A5*/

  /*write something*/
  kprintf("Hello L432KC\n");

  stm32l4_flash_getdevicesig(&sig);
  kprintf("Wafer #%d X=%d Y=%d\n",sig.waf_num,sig.waf_x,sig.waf_y);
  kprintf("Lot num: [%s]\n", sig.lotnum);
  kprintf("package: %d, Flash size %dKB\n",sig.package, sig.flashsize);

//  armv7m_systick_callback(systick_irq, NULL);


}

/*----------------------------------------------------------------------------*/
void eraseflash(void)
{
  uint32_t start, end;
  bool ret;

  start = (uint32_t)&_userflash_start;
  end   = stm32l4_flash_end();

  kprintf("Erasing the rest of flash, start addr=0x%x end addr=0x%x\n", start,end);

  while(start < end)
    {
      kprintf("Erasing at %x: ",start);
      ret = stm32l4_flash_erase(start);
      kprintf("%s\n", ret?"success":"failure");
      start += STM32L4_FLASH_ERASESIZE;
    }
  kprintf("Done.\n");

}

/*----------------------------------------------------------------------------*/
void board_main(void)
{
  uint32_t i;
  uint32_t state = 0;
  handle_t ha,hb;

  heap_init(&heap, heap_data, sizeof(heap_data));

  /* Heap 1000 bytes, zero handles, 1000 bytes available */
  /* One freeblock, 1000 bytes */

  ha = heap_alloc(&heap, 10);

  /* Allocated one handle, remains 1000 - 12 - 16 = 972 bytes */
  /* One freeblock, 974 bytes */

  hb = heap_alloc(&heap, 20);

  /* Allocated one more handle, remains 972 - 20 - 16 = 936 bytes */
  /* One free block, 938 bytes */

  heap_free(&heap, ha);

  /* One 10-bytes hole created at address zero */
  /* Two freeblocks:
   * - one at base size 12 bytes
   * - one at base + 30
   * This releases 12 bytes
   */


  /* Loop blinking led */
  while(1)
    {
      stm32l4_gpio_write(LED, state);
      state = !state;
      for(i=0;i<100000;i++) {};
    }
}


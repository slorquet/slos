#include <stdint.h>
#include <stddef.h>
#include <slos/stdio.h>

#include "armv8m_systick.h"
#include "armv8m_nvic.h"

#include "saml11_gpio.h"
#include "saml11_uart.h"

#include <slos/heap.h>

/*==============================================================================
 * Definitions
 *==============================================================================
 */

/* nucleo led on arduino D13 (PB3) */
//#define LED (GPIO_PORT_B | GPIO_PIN_3)

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
//  saml11_gpio_init(LED | GPIO_MODE_OUT | GPIO_PULL_UP | GPIO_TYPE_PP ); /*LED PIN ON A5*/

  /*write something*/
  kprintf("Hello SAML11\n");

//  armv8m_systick_callback(systick_irq, NULL);

}

/*----------------------------------------------------------------------------*/
void board_main(void)
{
  uint32_t i;
  uint32_t state = 0;
  handle_t ha,hb,hc;

  heap_init(&heap, heap_data, sizeof(heap_data));
  heap_dump(&heap);

  ha = heap_alloc(&heap, 10);
  heap_dump(&heap);

  hb = heap_alloc(&heap, 20);
  heap_dump(&heap);

  heap_free(&heap, ha);
  heap_dump(&heap);

  hc = heap_alloc(&heap, 15);
  heap_dump(&heap);

  heap_free(&heap, hc);
  heap_dump(&heap);

  hc = heap_alloc(&heap, 12);
  heap_dump(&heap);

  heap_free(&heap, hc);
  heap_dump(&heap);

  /* Loop blinking led */
  while(1)
    {
      //saml11_gpio_write(LED, state);
      state = !state;
      for(i=0;i<100000;i++) {};
    }
}


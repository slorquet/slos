//#include "config.h"

#include "chip.h"
#include "irq.h"
#include "bits/irq.h"

#include <stdint.h>

void arch_start(void); /*system entry point*/
void armv7m_irq(void);
void chip_irq(void);

/*symbols defined in linker script*/
extern uint32_t _stack_end;
extern uint32_t _bss_start;
extern uint32_t _bss_end;
extern uint32_t _data_init_start;
extern uint32_t _data_start;
extern uint32_t _data_end;

uint32_t _vectors[] __attribute__((section(".armvectors"))) = {
    /*Entries 0..15 are common for all ARMv7-M*/
    (uint32_t)&_stack_end, /*initial value for SP, defined in linkerscript*/
    (uint32_t)&arch_start, /*initial PC*/
    [ 2 ... 15] = (uint32_t)armv7m_irq,
    [16 ... 16 + ARCH_CHIP_NIRQS] = (uint32_t)chip_irq,
};

void board_start(void);

/*----------------------------------------------------------------------------*/
static inline void clearbss(void)
{
  uint32_t *addr;
  uint32_t *src;

  for(addr = &_bss_start; addr < &_bss_end; addr++)
    {
      *addr = 0;
    }
}

/*----------------------------------------------------------------------------*/
static inline void copydata(void)
{
  uint32_t *addr;
  uint32_t *src;

  src = &_data_init_start;
  for(addr = &_data_start; addr < &_data_end; addr++)
    {
      *addr = *src++;
    }
}

/*----------------------------------------------------------------------------*/
/*fist code executed by the CPU!*/
void arch_start(void)
{

  clearbss();

  copydata();

  /* Initialize common armv7m IRQs */

  armv7m_irq_init();

  /* Initialize peripherals */

  chip_start();

  /* Initialize board specific peripherals */

  board_start();

  /* Enable IRQs */

  armv7m_irq_enable();
}

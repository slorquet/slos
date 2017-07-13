#include <config.h>

#include "armv7m_systick.h"
#include "chip.h"
#include "irq.h"
#include "bits/irq.h"

#include <stdint.h>

void arch_start(void); /*system entry point*/
void armv7m_irqentry(void);

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
    [ 2 ... 15]                 = (uint32_t)armv7m_irqentry,
    [16 ... 16+ARCH_CHIP_NIRQS] = (uint32_t)armv7m_irqentry,
};

void board_start(void);
void board_main (void);

/*----------------------------------------------------------------------------*/
static inline void clearbss(void)
{
  uint32_t *addr;

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

  /* Setup the C execution environment */

  clearbss();

  copydata();

  /* Initialize common armv7m features */

  armv7m_irq_init();

#ifdef CONFIG_ARMV7M_SYSTICK
  armv7m_systick_init();
#endif

  /* Initialize system-on-chip peripherals */

  chip_start();

  /* Initialize board specific peripherals */

  board_start();

  /* Enable IRQs */

  armv7m_irq_enable();

  /* Start the OS (for now, in the board code) */

  board_main();
}

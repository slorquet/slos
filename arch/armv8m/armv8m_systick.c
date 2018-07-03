#include <config.h>

#include <stdint.h>
#include <stddef.h>

#include "armv8m.h"
#include "armv8m_nvic.h"
#include "armv8m_systick.h"


/*----------------------------------------------------------------------------*/
void armv8m_systick_init(void)
{
  uint32_t cal;

  cal = getreg32(ARMV8M_SYSTICK_CALIB);

  putreg32(ARMV8M_SYSTICK_RVR, cal);


  putreg32(ARMV8M_SYSTICK_CSR, SYSTICK_CSR_ENABLE | SYSTICK_CSR_TICKINT | SYSTICK_CSR_CLKSOURCE);
}

/*----------------------------------------------------------------------------*/
void armv8m_systick_callback(armv8m_irqhandler_f handler, void *arg)
{
  armv8m_irq_attach(ARMV8M_IRQ_SYSTICK, handler, arg);
  armv8m_irq_activate(ARMV8M_IRQ_SYSTICK, true);
}


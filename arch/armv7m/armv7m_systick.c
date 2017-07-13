#include <config.h>

#include <stdint.h>
#include <stddef.h>

#include "armv7m.h"
#include "armv7m_nvic.h"
#include "armv7m_systick.h"


/*----------------------------------------------------------------------------*/
void armv7m_systick_init(void)
{
  uint32_t cal;

  cal = getreg32(ARMV7M_SYSTICK_CALIB);

  putreg32(ARMV7M_SYSTICK_RVR, cal);


  putreg32(ARMV7M_SYSTICK_CSR, SYSTICK_CSR_ENABLE | SYSTICK_CSR_TICKINT | SYSTICK_CSR_CLKSOURCE);
}

/*----------------------------------------------------------------------------*/
void armv7m_systick_callback(armv7m_irqhandler_f handler, void *arg)
{
  armv7m_irq_attach(ARMV7M_IRQ_SYSTICK, handler, arg);
  armv7m_irq_activate(ARMV7M_IRQ_SYSTICK, true);
}


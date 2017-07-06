#include <config.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include <slos/stdio.h>

#include "armv7m.h"
#include "armv7m_nvic.h"
#include "armv7m_systick.h"

static uint32_t ctr;

void systick_irq(uint32_t irqno, void **context, void *arg)
{
  ctr++;

  if( (ctr % 1000)==0)
    kprintf("systick!\n");
}

void armv7m_systick_init(void)
{
  uint32_t cal;

  ctr=0;

  cal = getreg32(ARMV7M_SYSTICK_CALIB);

  putreg32(ARMV7M_SYSTICK_RVR, cal);

  armv7m_irq_attach(ARMV7M_IRQ_SYSTICK, systick_irq, NULL);
  armv7m_irq_activate(ARMV7M_IRQ_SYSTICK, true);

  putreg32(ARMV7M_SYSTICK_CSR, SYSTICK_CSR_ENABLE | SYSTICK_CSR_TICKINT | SYSTICK_CSR_CLKSOURCE);
}


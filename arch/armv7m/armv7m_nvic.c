#include <stdint.h>
#include <stddef.h>

#include "armv7m_nvic.h"
#include "irq.h"
#include "bits/irq.h"

static armv7m_irqhandler_t corehandlers[14]; /* Vectors 2..15 */
static armv7m_irqhandler_t chiphandlers[ARCH_CHIP_NIRQS]; /* Vectors 16..N */
static void*               chipargs    [ARCH_CHIP_NIRQS]; /* Vectors 16..N */

/*----------------------------------------------------------------------------*/
void armv7m_irq_init(void)
{
  int i;

  /* Initialize all irq handlers to non-defined state */

  for(i=0;i<sizeof(corehandlers)/sizeof(corehandlers[0]);i++)
    {
      corehandlers[i] = 0;
    }

  for(i=0;i<sizeof(chiphandlers)/sizeof(chiphandlers[0]);i++)
    {
      chiphandlers[i] = 0;
      chipargs    [i] = NULL;
    }

  /* Set all priorities to zero */
}

/*----------------------------------------------------------------------------*/
void armv7m_irq_attach(uint8_t irqno, armv7m_irqhandler_t handler, void *arg)
{
  if (irqno < 2)
    {
      return;
    }

  if (irqno < 16)
    {
      corehandlers[irqno-2] = handler;
    }
  else
    {
      chiphandlers[irqno-16] = handler;
      chipargs    [irqno-16] = arg;
    }
}

/*----------------------------------------------------------------------------*/
void armv7m_irq_activate(uint8_t irqno, bool state)
{
  if (irqno < 2)
    {
      return;
    }

  /* All core interrupts are managed in the first set of NVIC regs */

}

/*----------------------------------------------------------------------------*/
/* Called at Core interrupt */
void armv7m_irq(void)
{
  int irqno;

  /* Get the number of the active interrupt in IPSR */

  /* Compute table index */
  //irqno -= 2;

  /* Check that a handler is attached */
  if(corehandlers[irqno]==0)
    {
      return;
    }

  /* Call the handler */
  corehandlers[irqno](irqno, NULL);
}

/*----------------------------------------------------------------------------*/
/* Called at SoC interrupt */
void chip_irq(void)
{
  int irqno;

  /* Get the number of the active interrupt in IPSR */

  /* Compute table index */
  //irqno -= 16;

  /* Check that a handler is attached */
  if(chiphandlers[irqno]==0)
    {
      return;
    }

  /* Call the handler */
  chiphandlers[irqno](irqno, chipargs[irqno]);
}


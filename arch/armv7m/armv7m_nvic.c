#include <stdint.h>
#include "armv7m_nvic.h"
#include "irq.h"
static armv7m_irqhandler_t handlers[14]; /* Vectors 2..15 */

/*----------------------------------------------------------------------------*/
void armv7m_irq_init(void)
{
  int i;

  /* Initialize all irq handlers to non-defined state */

  for(i=0;i<sizeof(handlers)/sizeof(handlers[0]);i++)
    {
      handlers[i] = 0;
    }

  /* Set all priorities to zero */
}

/*----------------------------------------------------------------------------*/
void armv7m_irq_attach(uint8_t irqno, armv7m_irqhandler_t handler)
{
  if(irqno < 2 || irqno > 15)
    {
      return;
    }
  handlers[irqno-2] = handler;
}

/*----------------------------------------------------------------------------*/
void armv7m_irq_activate(uint8_t irqno, bool state)
{
  if(irqno < 2 || irqno > 15)
    {
      return;
    }

  /* All core interrupts are managed in the first set of NVIC regs */

}

/*----------------------------------------------------------------------------*/
/* Called at interrupt */
void armv7m_irq(void)
{
  int irqno;

  /* Get the number of the active interrupt in IPSR */

  /* Check that a handler is attached */
  if(handlers[irqno]==0)
    {
      return;
    }

  /* Call the handler */
  handlers[irqno](0);

}


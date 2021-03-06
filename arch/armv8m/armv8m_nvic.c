#include <stdint.h>
#include <stddef.h>

#include "armv8m.h"
#include "armv8m_nvic.h"
#include "bits/irq.h"

static armv8m_irqhandler_f handlers[14+ARCH_CHIP_NIRQS]; /* Vectors 2..15 and 16..N */
static void*               args    [14+ARCH_CHIP_NIRQS]; /* Args for vectors 2..15 and 16..N */

/*----------------------------------------------------------------------------*/
void armv8m_irq_init(void)
{
  /* Initialize all irq handlers to non-defined state */
  /* BSS initialized to zero: not required */
#if 0
  for(i=0;i<sizeof(handlers)/sizeof(handlers[0]);i++)
    {
      handlers[i] = 0;
      args    [i] = NULL;
    }
#endif

  /* Set all priorities to zero */
  asm volatile(
    "\tmov r0, #0\n"
    "\tmsr basepri, r0\n"
  );
}

/*----------------------------------------------------------------------------*/
void armv8m_irq_enable(void)
{
  asm volatile(
    "cpsie i"
  );
}

/*----------------------------------------------------------------------------*/
void armv8m_irq_disable(void)
{
  asm volatile(
    "cpsid i"
  );
}

/*----------------------------------------------------------------------------*/
void armv8m_irq_attach(uint32_t irqno, armv8m_irqhandler_f handler, void *arg)
{
  if (irqno < 2)
    {
      return;
    }

  irqno -= 2;

  handlers[irqno] = handler;
  args    [irqno] = arg;
}

/*----------------------------------------------------------------------------*/
void armv8m_irq_activate(uint32_t irqno, bool state)
{
  uint32_t regmask;

  if (irqno < 2)
    {
      return;
    }

  /* Compute enable/disable bit in reg. There are 32 irq per reg */
  regmask = irqno & 0x1F;

  /* Turn into a mask */
  regmask = 1<<regmask;

  /* Select the proper register */
  irqno >>= 5;

  if (state)
    {
      irqno += ARMV8M_NVIC_REGBASE_ISER;
    }
  else
    {
      irqno += ARMV8M_NVIC_REGBASE_ICER;
    }

  putreg32(irqno, regmask);
 
}

/*----------------------------------------------------------------------------*/
/* The return value of this function is the SP from where the irq frame should be popped.
 * If no context switching is implied, always return unmodified sp. */
void* armv8m_irq(void *sp, uint32_t irqno)
{
  /* Compute table index */
  irqno -= 2;

  /* Check that a handler is attached */
  if(handlers[irqno]!=0)
    {
      /* Call the handler */
      handlers[irqno](irqno+2, &sp, args[irqno]);
    }

  return sp;
}

/*----------------------------------------------------------------------------*/
void __attribute__((naked)) armv8m_irqentry(void)
{
  asm volatile
  (
    "mov  r0, sp     \n" /* Save SP that points to the irq stack frame */
    "push {lr}       \n" /* Backup the LR, this is the only one that must not be messed up */
    "mrs  r1, ipsr   \n" /* Get the IRQ number */
    "bl   armv8m_irq \n" /* Call into C with args in r0,r1 */
    "pop  {r1}       \n" /* Restore LR via R1*/
    "mov  lr, r1     \n" /* ARMv6m cannot directly pop LR */
    "mov  sp, r0     \n" /* Get new SP from C code */
    "bx   lr         \n" /* Magic EXC_RETURN */
    :::
    "r0", "r1", "lr", "sp" /* Clobber list */
  );
}

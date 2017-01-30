#ifndef __ARMV7M__IRQ__H__
#define __ARMV7M__IRQ__H__

#include <stdint.h>
#include <stdbool.h>

static inline void armv7m_irq_enable(void)
{
  uint32_t bp=0;
  asm volatile(
    "\tmov r0, #0\n"
    "\tmrs r0, basepri\n"
    "\tcpsie i"
  );
}

static inline armv7m_irq_disable(void)
{
  asm volatile("cpsid i");
}

typedef void (*armv7m_irqhandler_t)(int irqno, void *arg);

void armv7m_irq_init(void);
void armv7m_irq_attach(uint32_t irqno, armv7m_irqhandler_t handler, void *arg);
void armv7m_irq_activate(uint32_t irqno, bool state);

#endif

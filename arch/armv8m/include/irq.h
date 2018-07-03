#ifndef __ARMV8M__IRQ__H__
#define __ARMV8M__IRQ__H__

#include <stdint.h>
#include <stdbool.h>

#include "armv8m_nvic.h"

#define irq_enable() armv8m_irq_enable()
#define irq_disable() armv8m_irq_disable()

#define irq_attach(irqno, handler, arg) armv8m_irq_attach(irqno, handler, arg)
#define irq_activate(irqno, state)      armv8m_irq_activate(irqno, state)

#endif

#ifndef __ARMV7M__IRQ__H__
#define __ARMV7M__IRQ__H__

#include <stdint.h>
#include <stdbool.h>

#include "armv7m_nvic.h"

#define irq_enable() armv7m_irq_enable()
#define irq_disable() armv7m_irq_disable()

#define irq_attach(irqno, handler, arg) armv7m_irq_attach(irqno, handler, arg)
#define irq_activate(irqno, state)      armv7m_irq_activate(irqno, state)

#endif

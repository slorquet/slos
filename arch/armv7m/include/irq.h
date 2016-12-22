#ifndef __ARMV7M__IRQ__H__
#define __ARMV7M__IRQ__H__

#include <stdint.h>
#include <stdbool.h>

#define armv7m_irq_enable() asm("cpsie i")
#define armv7m_irq_disable() asm("cpsid i")

typedef void (*armv7m_irqhandler_t)(void *arg);

void armv7m_irq_init(void);
void armv7m_irq_attach(uint8_t irqno, armv7m_irqhandler_t handler);
void armv7m_irq_activate(uint8_t irqno, bool state);

#endif

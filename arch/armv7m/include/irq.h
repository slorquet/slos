#ifndef __ARMV7M__IRQ__H__
#define __ARMV7M__IRQ__H__

#include <stdint.h>
#include <stdbool.h>

typedef void (*armv7m_irqhandler_t)(void *arg);

void armv7m_irq_init(void);
void armv7m_irq_attach(uint8_t irqno, armv7m_irqhandler_t handler);
void armv7m_irq_enable(uint8_t irqno, bool state);

#endif

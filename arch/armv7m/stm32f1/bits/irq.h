#ifndef __ARCH__ARMV6M__STM32F1__BITS__IRQ__H__
#define __ARCH__ARMV6M__STM32F1__BITS__IRQ__H__

#include "config.h"
#if defined( CONFIG_STM32F1_LINE_CONNECTIVITY )
#include "irq_connectivity.h"
#elif defined( CONFIG_STM32F1_LINE_XLDENSITY )
#include "irq_xldensity.h"
#else
#include "irq_others.h"
#endif

void armv7m_irq_init(void);
void armv7m_irq_enable(void);

#endif

#ifndef __ARCH__ARMV7M__STM32F1__BITS__IRQ__H__
#define __ARCH__ARMV7M__STM32F1__BITS__IRQ__H__

#include <config.h>
#if defined( CONFIG_STM32F1_LINE_CONNECTIVITY )
#include "bits/irq_connectivity.h"
#elif defined( CONFIG_STM32F1_LINE_XLDENSITY )
#include "bits/irq_xldensity.h"
#else
#include "bits/irq_others.h"
#endif

#endif

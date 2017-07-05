#ifndef _ARCH_ARMV7M_STM32L4_BITS_STM32L4_RCC_H_
#define _ARCH_ARMV7M_STM32L4_BITS_STM32L4_RCC_H_

#if defined( ARCH_CHIPFAMILY_STM32L4X6 )
#include "bits/stm32l4x6xx_rcc.h"
#elif defined( ARCH_CHIPFAMILY_STM32L4X3 )
#include "bits/stm32l4x3xx_rcc.h"
#else
#error undefined STM32L4 family
#endif

#endif

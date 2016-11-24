#ifndef _ARCH_ARMV7M_STM32L4_STM32L4_RCC_H_
#define _ARCH_ARMV7M_STM32L4_STM32L4_RCC_H_

#include <stdint.h>
#include <bits/stm32l4_periphs.h>
#include <bits/stm32l4_rcc.h>

void stm32l4_clock_default(void);
uint32_t stm32l4_clock_get(void);

#endif /* _ARCH_ARMV7M_STM32L4_STM32L4_RCC_H_*/

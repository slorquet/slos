#ifndef _ARCH_ARMV7M_STM32F4_STM32F4_RCC_H_
#define _ARCH_ARMV7M_STM32F4_STM32F4_RCC_H_

#include <stdint.h>
#include <bits/stm32f4_periphs.h>
#include <bits/stm32f4_rcc.h>

void stm32f4_clock_default(void);
uint32_t stm32f4_clock_get(void);

#endif /* _ARCH_ARMV7M_STM32F4_STM32F4_RCC_H_*/

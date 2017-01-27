#ifndef __ARCH__ARMV7M__STM32F1__STM32F1__RCC__H__
#define __ARCH__ARMV7M__STM32F1__STM32F1__RCC__H__

#include <stdint.h>
#include <stdbool.h>

bool stm32f1_rtc_init(uint32_t prescaler);
uint32_t stm32f1_rtc_read(void);

#endif /* __ARCH_ARMV7M__STM32F1__STM32F1__RTC__H__ */


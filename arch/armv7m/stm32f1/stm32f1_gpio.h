#ifndef __ARCH__ARMV6M__STM32F1__STM32F1__GPIO__H__
#define __ARCH__ARMV6M__STM32F1__STM32F1__GPIO__H__

#include <stdint.h>
#include <stdbool.h>

void stm32f1_gpioconfig(uint32_t descriptor);
void stm32f1_gpiowrite(uint32_t gpio, bool state);

#endif /* __ARCH__ARMV6M__STM32F1__STM32F1__GPIO__H__ */

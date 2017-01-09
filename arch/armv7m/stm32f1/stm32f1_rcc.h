#ifndef __ARCH__ARMV6M__STM32F1__STM32F1__RCC__H__
#define __ARCH__ARMV6M__STM32F1__STM32F1__RCC__H__

#include <stdint.h>
#include <stdbool.h>

struct stm32f1_clocks_s
{
  uint32_t sysclk; /* Main SYSCLK, MAX 72 MHz */
  uint32_t hclk;   /* AHB clock = SYSCLK / AHB prescaler, MAX 72 MHz */
  uint32_t pclk1;  /* APB1 main clock = HCLK / APB1 prescaler, MAX 36 MHz */
  uint32_t tclk1;  /* APB1 timers clock = PCLK1 if APB1 prescaler=1, else PCLK1*2 */
  uint32_t pclk2;  /* APB2 main clock = HCLK / APB2 prescaler */
  uint32_t tclk2;  /* APB2 timers clock = PCLK2 if APB2 prescaler=1, else PCLK2*2 */
  uint32_t adcclk; /* ADC clock = PCLK2 / ADC prescaler */
  /* TODO overflow flags */
};

typedef void (*stm32f1_clockhook_f)(void);

void stm32f1_clock_setup(void);
struct stm32f1_clocks_s * stm32f1_clock_getinfo(void);
bool stm32f1_ahbprescaler(uint32_t prescaler);
bool stm32f1_apb1prescaler(uint32_t prescaler);
bool stm32f1_apb2prescaler(uint32_t prescaler);
bool stm32f1_adcprescaler(uint32_t prescaler);
bool stm32f1_clock_registerhook(stm32f1_clockhook_f hook);

#endif /* __ARCH__ARMV6M__STM32F1__STM32F1__RCC__H__ */

#ifndef __ARCH__ARMV7M__STM32F1__STM32F1__RCC__H__
#define __ARCH__ARMV7M__STM32F1__STM32F1__RCC__H__

#include <stdint.h>
#include <stdbool.h>

/*==============================================================================
 * Definitions
 *==============================================================================
 */

/* Options for RTC clock source */
enum
{
  RTC_SRC_NONE,  /* No clock provided to RTC */
  RTC_SRC_LSE,   /* RTC clocked via low speed ext xtal (32.768 kHz, must be enabled before) */
  RTC_SRC_LSI,   /* RTC clocked via low speed int osc (40 kHz, must be enabled before) */
  RTC_SRC_HSE128 /* RTC clocked via high ext speed xtal / 128 (must be enabled before) */
};

/*==============================================================================
 * Types
 *==============================================================================
 */

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

/*==============================================================================
 * Function Prototypes
 *==============================================================================
 */

void stm32f1_clock_setup(void);

/* System clock tree management */

struct stm32f1_clocks_s * stm32f1_clock_getinfo(void);
bool stm32f1_ahbprescaler(uint32_t prescaler);
bool stm32f1_apb1prescaler(uint32_t prescaler);
bool stm32f1_apb2prescaler(uint32_t prescaler);
bool stm32f1_adcprescaler(uint32_t prescaler);

void stm32f1_clock_enablebkp(void);

/* Individual clocks enable */

bool stm32f1_clock_lse_enable(bool state);
bool stm32f1_clock_lse_ready(void);

bool stm32f1_clock_hse_enable(bool state);
bool stm32f1_clock_hse_ready(void);

bool stm32f1_clock_hsi_ready(void);

bool stm32f1_clock_lsi_ready(void);

/* Clock selection for configurable peripherals */

bool stm32f1_clock_rtc(int rtcclocksource);

/* Clock change hooks management */

bool stm32f1_clock_registerhook(stm32f1_clockhook_f hook);

#endif /* __ARCH__ARMV6M__STM32F1__STM32F1__RCC__H__ */

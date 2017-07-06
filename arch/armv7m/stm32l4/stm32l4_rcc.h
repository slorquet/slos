#ifndef _ARCH_ARMV7M_STM32L4_STM32L4_RCC_H_
#define _ARCH_ARMV7M_STM32L4_STM32L4_RCC_H_

#include <stdint.h>
#include <stdbool.h>

/* Options for RTC clock source */
enum
{
  RTC_SRC_NONE,  /* No clock provided to RTC */
  RTC_SRC_LSE,   /* RTC clocked via low speed ext xtal (32.768 kHz, must be enabled before) */
  RTC_SRC_LSI,   /* RTC clocked via low speed int osc (40 kHz, must be enabled before) */
  RTC_SRC_HSE32  /* RTC clocked via high ext speed xtal / 32 (must be enabled before) */
};

/* Options for 48M clock source */
enum
{
  FEM_SRC_NONE,    /* No clock provided to 48M */
  FEM_SRC_PLLMAIN, /* 48M clocked via main PLL (must be enabled before) */
  FEM_SRC_PLLSAI1, /* 48M clocked via SAI1 PLL (must be enabled before) */
  FEM_SRC_MSI    /* 48M clocked via MSI (must be enabled before) */
};

/* Options for ADC clock source */
enum
{
  ADC_SRC_NONE,    /* No clock provided to ADC */
  ADC_SRC_SYSCLK,  /* ADC clocked via SYSCLK */
  ADC_SRC_PLLSAI1, /* ADC clocked via SAI1 PLL (must be enabled before) */
  ADC_SRC_PLLSAI2, /* ADC clocked via SAI2 PLL (must be enabled before) */
};

/* Options for USART clock source */
/* Options for I2C clock source */
/* Options for SAI1 clock source */
/* Options for SAI2 clock source */
/* Options for SWPMI1 clock source */
/* Options for LPTIMx clock source */

/*==============================================================================
 * Types
 *==============================================================================
 */

struct stm32l4_clocks_s
{
  uint32_t sysclk; /* Main SYSCLK, MAX 80 MHz */
  uint32_t hclk;   /* AHB clock = SYSCLK / AHB prescaler, MAX ?? MHz */
  uint32_t pclk1;  /* APB1 main clock = HCLK / APB1 prescaler, MAX ?? MHz */
  uint32_t tclk1;  /* APB1 timers clock = PCLK1 if APB1 prescaler=1, else PCLK1*2 */
  uint32_t pclk2;  /* APB2 main clock = HCLK / APB2 prescaler */
  uint32_t tclk2;  /* APB2 timers clock = PCLK2 if APB2 prescaler=1, else PCLK2*2 */
  /* TODO overflow flags */
};

typedef void (*stm32l4_clockhook_f)(void);

/*==============================================================================
 * Function Prototypes
 *==============================================================================
 */

void stm32l4_clock_setup(void);

/* System clock tree management */

struct stm32l4_clocks_s * stm32l4_clock_getinfo(void);
bool stm32l4_ahbprescaler(uint32_t prescaler);
bool stm32l4_apb1prescaler(uint32_t prescaler);
bool stm32l4_apb2prescaler(uint32_t prescaler);

void stm32l4_clock_enablebkp(void);

/* Individual clocks enable */

bool stm32l4_clock_lse_enable(bool state);
bool stm32l4_clock_lse_ready(void);

bool stm32l4_clock_hse_enable(bool state);
bool stm32l4_clock_hse_ready(void);

bool stm32l4_clock_hsi_ready(void);

bool stm32l4_clock_lsi_ready(void);

/* Clock selection for configurable peripherals */

bool stm32l4_clock_rtc(int rtcclocksource);
bool stm32l4_clock_48M(int femclocksource);
bool stm32l4_clock_adc(int adcclocksource);

/* Clock change hooks management */

bool stm32l4_clock_registerhook(stm32l4_clockhook_f hook);

#endif /* _ARCH_ARMV7M_STM32L4_STM32L4_RCC_H_*/

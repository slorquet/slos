#include <config.h>

#include <stdint.h>
#include <stdbool.h>
#include "armv7m.h"

#include "bits/stm32l4_periphs.h"
#include "bits/stm32l4_rcc.h"
#include "bits/stm32l4_pwr.h"
#include "stm32l4_rcc.h"

/*==============================================================================
 * Definitions
 *==============================================================================
 */

/*==============================================================================
 * Types
 *==============================================================================
 */

struct stm32l4_prescalers_s /* TODO store as shifts */
{
  uint32_t psc_ahb;
  uint32_t psc_apb1;
  uint32_t psc_apb2;
  uint32_t mul_tim1;
  uint32_t mul_tim2; 
};

/*==============================================================================
 * Function Prototypes
 *==============================================================================
 */

static void stm32l4_clock_notifychange(void);

/*==============================================================================
 * Variables and constants
 *==============================================================================
 */

static struct stm32l4_clocks_s g_stm32l4_clocks; /* current system clock frequencies */

static struct stm32l4_prescalers_s g_stm32l4_prescalers =
{
  .psc_ahb  = 1,
  .psc_apb1 = 1,
  .psc_apb2 = 1,
  .mul_tim1 = 1,
  .mul_tim2 = 1,
};

uint8_t g_stm32l4_clockhookcount;
stm32l4_clockhook_f g_stm32l4_clockhooks[CONFIG_STM32L4_CLOCKHOOK_MAX];

/*==============================================================================
 * Functions
 *==============================================================================
 */

/*----------------------------------------------------------------------------*/
/* Recompute various clocks based on sysclk and prescalers*/
static void stm32l4_clock_recompute(void)
{
  /* page 102 AHB default prescaler = 1 (8 MHz, max 72 MHz) */
  g_stm32l4_clocks.hclk = g_stm32l4_clocks.sysclk / g_stm32l4_prescalers.psc_ahb;
  
  /* page 102 APB1 default prescaler = 1 (8 MHz, max 36 MHz) */
  g_stm32l4_clocks.pclk1 = g_stm32l4_clocks.hclk / g_stm32l4_prescalers.psc_apb1;

  /* This default value means TCLK1 = 2 * PCLK1 (16 MHz, max ?? MHz) */
  g_stm32l4_clocks.tclk1 = g_stm32l4_clocks.pclk1 * g_stm32l4_prescalers.mul_tim1;

  /* page 101 APB2 default prescaler = 1 (8 MHz, max 72 MHz) */
  g_stm32l4_clocks.pclk2 = g_stm32l4_clocks.hclk / g_stm32l4_prescalers.psc_apb2;
  
  /* This default value means TCLK2 = 2 * PCLK2 (16 MHz, max ?? MHz) */
  g_stm32l4_clocks.tclk2 = g_stm32l4_clocks.pclk2 * g_stm32l4_prescalers.mul_tim2;
}

/*----------------------------------------------------------------------------*/
void stm32l4_clock_setup(void)
{
  /*RM???? rev16 ?.?.? page ??: Default to HSI */
  g_stm32l4_clocks.sysclk = 4000000;

  stm32l4_clock_recompute();
}

/* System clock tree management */

/*----------------------------------------------------------------------------*/
struct stm32l4_clocks_s * stm32l4_clock_getinfo(void)
{
  return &g_stm32l4_clocks;
}

/*----------------------------------------------------------------------------*/
bool stm32l4_ahbprescaler(uint32_t prescaler)
{
  return false;
}

/*----------------------------------------------------------------------------*/
bool stm32l4_apb1prescaler(uint32_t prescaler)
{
  return false;
}

/*----------------------------------------------------------------------------*/
bool stm32l4_apb2prescaler(uint32_t prescaler)
{
  return false;
}

/*----------------------------------------------------------------------------*/
void stm32l4_clock_enablebkp(void)
{
}

/* Individual clocks enable */

/*----------------------------------------------------------------------------*/
bool stm32l4_clock_lse_enable(bool state)
{
  return false;
}

/*----------------------------------------------------------------------------*/
bool stm32l4_clock_lse_ready(void)
{
  uint32_t val = getreg32(STM32L4_REGBASE_RCC + STM32L4_RCC_BDCR);
  return (val & RCC_BDCR_LSERDY) == RCC_BDCR_LSERDY;
}

/*----------------------------------------------------------------------------*/
bool stm32l4_clock_hse_enable(bool state)
{
  return false;
}

/*----------------------------------------------------------------------------*/
bool stm32l4_clock_hse_ready(void)
{
  uint32_t val = getreg32(STM32L4_REGBASE_RCC + STM32L4_RCC_CR);
  return (val & RCC_CR_HSERDY) == RCC_CR_HSERDY;
}

/*----------------------------------------------------------------------------*/
bool stm32l4_clock_hsi_ready(void)
{
  uint32_t val = getreg32(STM32L4_REGBASE_RCC + STM32L4_RCC_CR);
  return (val & RCC_CR_HSIRDY) == RCC_CR_HSIRDY;
}

/*----------------------------------------------------------------------------*/
bool stm32l4_clock_lsi_ready(void)
{
  uint32_t val = getreg32(STM32L4_REGBASE_RCC + STM32L4_RCC_CSR);
  return (val & RCC_CSR_LSIRDY) == RCC_CSR_LSIRDY;
}

/*----------------------------------------------------------------------------*/
bool stm32l4_clock_msi_ready(void)
{
  uint32_t val = getreg32(STM32L4_REGBASE_RCC + STM32L4_RCC_CR);
  return (val & RCC_CR_MSIRDY) == RCC_CR_MSIRDY;
}


/* Clock selection for configurable peripherals */

/*----------------------------------------------------------------------------*/
bool stm32l4_clock_rtc(int rtcclocksource)
{
  return false;
}

/*----------------------------------------------------------------------------*/
bool stm32l4_clock_48M(int femclocksource)
{
  return false;
}

/*----------------------------------------------------------------------------*/
bool stm32l4_clock_adc(int adcclocksource)
{
  return false;
}

/* Clock change hooks management */

/*----------------------------------------------------------------------------*/
bool stm32l4_clock_registerhook(stm32l4_clockhook_f hook)
{
  return false;
}



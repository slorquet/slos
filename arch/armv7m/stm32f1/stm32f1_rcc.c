#include <stdint.h>
#include <stdbool.h>
#include "armv7m.h"

#include "bits/stm32f1_periphs.h"
#include "bits/stm32f1_rcc.h"
#include "bits/stm32f1_pwr.h"
#include "stm32f1_rcc.h"

/*==============================================================================
 * Definitions
 *==============================================================================
 */

/*==============================================================================
 * Types
 *==============================================================================
 */

struct stm32f1_prescalers_s /* TODO store as shifts */
{
  uint32_t psc_ahb;
  uint32_t psc_apb1;
  uint32_t psc_apb2;
  uint32_t psc_adc;
  uint32_t mul_tim1;
  uint32_t mul_tim2; 
};

/*==============================================================================
 * Function Prototypes
 *==============================================================================
 */

static void stm32f1_clock_notifychange(void);

/*==============================================================================
 * Variables and constants
 *==============================================================================
 */

static struct stm32f1_clocks_s g_stm32f1_clocks; /* current system clock frequencies */

static struct stm32f1_prescalers_s g_stm32f1_prescalers =
{
  .psc_ahb  = 1,
  .psc_apb1 = 1,
  .psc_apb2 = 1,
  .psc_adc  = 1,
  .mul_tim1 = 1,
  .mul_tim2 = 1,
};

uint8_t g_stm32f1_clockhookcount;
stm32f1_clockhook_f g_stm32f1_clockhooks[CONFIG_STM32F1_CLOCKHOOK_MAX];

/*==============================================================================
 * Functions
 *==============================================================================
 */

/*----------------------------------------------------------------------------*/
/* Recompute various clocks based on sysclk and prescalers*/
static void stm32f1_clock_recompute(void)
{
  /* page 102 AHB default prescaler = 1 (8 MHz, max 72 MHz) */
  g_stm32f1_clocks.hclk = g_stm32f1_clocks.sysclk / g_stm32f1_prescalers.psc_ahb;
  
  /* page 102 APB1 default prescaler = 1 (8 MHz, max 36 MHz) */
  g_stm32f1_clocks.pclk1 = g_stm32f1_clocks.hclk / g_stm32f1_prescalers.psc_apb1;

  /* This default value means TCLK1 = 2 * PCLK1 (16 MHz, max ?? MHz) */
  g_stm32f1_clocks.tclk1 = g_stm32f1_clocks.pclk1 * g_stm32f1_prescalers.mul_tim1;

  /* page 101 APB2 default prescaler = 1 (8 MHz, max 72 MHz) */
  g_stm32f1_clocks.pclk2 = g_stm32f1_clocks.hclk / g_stm32f1_prescalers.psc_apb2;
  
  /* This default value means TCLK2 = 2 * PCLK2 (16 MHz, max ?? MHz) */
  g_stm32f1_clocks.tclk2 = g_stm32f1_clocks.pclk2 * g_stm32f1_prescalers.mul_tim2;

  /* page 101 ADC default prescaler = 2 (4 MHz, max 14 MHz) */
  g_stm32f1_clocks.adcclk = g_stm32f1_clocks.pclk2 / g_stm32f1_prescalers.psc_adc;
}

/*----------------------------------------------------------------------------*/
void stm32f1_clock_setup(void)
{
  /*RM0008 rev16 7.2.6 page 96: Default to HSI */
  g_stm32f1_clocks.sysclk = 8000000;

  stm32f1_clock_recompute();
}

/*----------------------------------------------------------------------------*/
struct stm32f1_clocks_s * stm32f1_clock_getinfo(void)
{
  return &g_stm32f1_clocks;
}

/*----------------------------------------------------------------------------*/
bool stm32f1_clock_ahbprescaler(uint32_t prescaler)
{
  uint32_t val = getreg32(STM32F1_REGBASE_RCC+STM32F1_RCC_CFGR);
  val &= ~RCC_CFGR_HPRE_MASK;
  switch(prescaler)
    {
    case 1:   val |= RCC_CFGR_HPRE_DIV1;   break;
    case 2:   val |= RCC_CFGR_HPRE_DIV2;   break;
    case 4:   val |= RCC_CFGR_HPRE_DIV4;   break;
    case 8:   val |= RCC_CFGR_HPRE_DIV8;   break;
    case 16:  val |= RCC_CFGR_HPRE_DIV16;  break;
    case 64:  val |= RCC_CFGR_HPRE_DIV64;  break;
    case 128: val |= RCC_CFGR_HPRE_DIV128; break;
    case 256: val |= RCC_CFGR_HPRE_DIV256; break;
    case 512: val |= RCC_CFGR_HPRE_DIV512; break;
    default:  return false;
    }
  putreg32(STM32F1_REGBASE_RCC+STM32F1_RCC_CFGR, val);

  g_stm32f1_prescalers.psc_ahb = prescaler;
  stm32f1_clock_recompute();
  stm32f1_clock_notifychange();
  return true;
}

/*----------------------------------------------------------------------------*/
bool stm32f1_clock_apb1prescaler(uint32_t prescaler)
{
  uint32_t val = getreg32(STM32F1_REGBASE_RCC+STM32F1_RCC_CFGR);
  val &= ~RCC_CFGR_PPRE1_MASK;
  switch(prescaler)
    {
      case 1:  val |= RCC_CFGR_PPRE1_DIV1;  break;
      case 2:  val |= RCC_CFGR_PPRE1_DIV2;  break;
      case 4:  val |= RCC_CFGR_PPRE1_DIV4;  break;
      case 8:  val |= RCC_CFGR_PPRE1_DIV8;  break;
      case 16: val |= RCC_CFGR_PPRE1_DIV16; break;
    default:  return false;
    }
  putreg32(STM32F1_REGBASE_RCC+STM32F1_RCC_CFGR, val);

  g_stm32f1_prescalers.psc_apb1 = prescaler;
  if(prescaler==1)
    {
      g_stm32f1_prescalers.mul_tim1 = 1;
    }
  else
    {
      g_stm32f1_prescalers.mul_tim1 = 2;
    }
  stm32f1_clock_recompute();
  stm32f1_clock_notifychange();
  return true;
}

/*----------------------------------------------------------------------------*/
bool stm32f1_clock_apb2prescaler(uint32_t prescaler)
{
  uint32_t val = getreg32(STM32F1_REGBASE_RCC+STM32F1_RCC_CFGR);
  val &= ~RCC_CFGR_PPRE2_MASK;
  switch(prescaler)
    {
      case 1:  val |= RCC_CFGR_PPRE2_DIV1;  break;
      case 2:  val |= RCC_CFGR_PPRE2_DIV2;  break;
      case 4:  val |= RCC_CFGR_PPRE2_DIV4;  break;
      case 8:  val |= RCC_CFGR_PPRE2_DIV8;  break;
      case 16: val |= RCC_CFGR_PPRE2_DIV16; break;
    default:  return false;
    }
  putreg32(STM32F1_REGBASE_RCC+STM32F1_RCC_CFGR, val);

  g_stm32f1_prescalers.psc_apb2 = prescaler;
  if(prescaler==1)
    {
      g_stm32f1_prescalers.mul_tim2 = 1;
    }
  else
    {
      g_stm32f1_prescalers.mul_tim2 = 2;
    }
  stm32f1_clock_recompute();
  stm32f1_clock_notifychange();
  return true;
}

/*----------------------------------------------------------------------------*/
bool stm32f1_clock_adcprescaler(uint32_t prescaler)
{
  uint32_t val = getreg32(STM32F1_REGBASE_RCC+STM32F1_RCC_CFGR);
  val &= ~RCC_CFGR_ADCPRE_MASK;
  switch(prescaler)
    {
      case 2: val |= RCC_CFGR_ADCPRE_DIV2; break;
      case 4: val |= RCC_CFGR_ADCPRE_DIV4; break;
      case 6: val |= RCC_CFGR_ADCPRE_DIV6; break;
      case 8: val |= RCC_CFGR_ADCPRE_DIV8; break;
    default:  return false;
    }
  putreg32(STM32F1_REGBASE_RCC+STM32F1_RCC_CFGR, val);

  g_stm32f1_prescalers.psc_adc = prescaler;
  stm32f1_clock_recompute();
  stm32f1_clock_notifychange();
  return true;
}

/*----------------------------------------------------------------------------*/
bool stm32f1_clock_enablelse(void)
{
  int tries = 1000;
  uint32_t val;

  /* Enable power control */

  val  = getreg32(STM32F1_REGBASE_RCC+STM32F1_RCC_APB1ENR);
  val |= RCC_APB1ENR_PWREN | RCC_APB1ENR_BKPEN;
  putreg32(STM32F1_REGBASE_RCC+STM32F1_RCC_APB1ENR, val);

  /* Ensure access to backup domain is enabled */

  val  = getreg32(STM32F1_REGBASE_PWR+STM32F1_PWR_CR);
  val |= PWR_CR_DBP;
  putreg32(STM32F1_REGBASE_PWR+STM32F1_PWR_CR, val);

  /* Enable LSE */

  val  = getreg32(STM32F1_REGBASE_RCC+STM32F1_RCC_BDCR);
  val |= RCC_BDCR_LSEON;
  putreg32(STM32F1_REGBASE_RCC+STM32F1_RCC_BDCR, val);

  /* Wait for LSE ready */

  while( tries > 0)
    {
      val = getreg32(STM32F1_REGBASE_RCC+STM32F1_RCC_BDCR);
      if(val & RCC_BDCR_LSERDY)
        {
          break;
        }
        tries-=1; /* Try again */
    }

  return val & RCC_BDCR_LSERDY;
}

/*----------------------------------------------------------------------------*/
/* Store a clock hook, to be called when a clock changes */
bool stm32f1_clock_registerhook(stm32f1_clockhook_f hook)
{
  if(g_stm32f1_clockhookcount < CONFIG_STM32F1_CLOCKHOOK_MAX)
    {
    g_stm32f1_clockhooks[g_stm32f1_clockhookcount++] = hook;
    return true;
    }
  return false;
}
/*----------------------------------------------------------------------------*/
static void stm32f1_clock_notifychange(void)
{
  int i;
  for(i = 0; i < g_stm32f1_clockhookcount; i++)
  {
    g_stm32f1_clockhooks[i]();
  }  
}

#include <stdint.h>

#include "armv7m.h"

#include "bits/stm32f1_periphs.h"
#include "bits/stm32f1_rcc.h"
#include "stm32f1_rcc.h"

static struct stm32f1_clocks_s g_stm32f1_clocks; /* current system clock frequencies */

struct stm32f1_prescalers_s
{
  uint32_t psc_ahb;
  uint32_t psc_apb1;
  uint32_t psc_apb2;
  uint32_t psc_adc;
  uint32_t mul_tim1;
  uint32_t mul_tim2; 
};

static struct stm32f1_prescalers_s g_stm32f1_prescalers =
{
  .psc_ahb  = 1,
  .psc_apb1 = 1,
  .psc_apb2 = 1,
  .psc_adc  = 1,
  .mul_tim1 = 2,
  .mul_tim2 = 2,
};

/*----------------------------------------------------------------------------*/
void stm32f1_clock_setup(void)
{
  /*RM0008 rev16 7.2.6 page 96: Default to HSI (8 MHz, max 72 MHz) */
  g_stm32f1_clocks.sysclk = 8000000;

  /* page 102 AHB default prescaler = 1 (8 MHz, max 72 MHz) */
  g_stm32f1_clocks.hclk = g_stm32f1_clocks.sysclk;
  
  /* page 102 APB1 default prescaler = 1 (8 MHz, max 36 MHz) */
  g_stm32f1_clocks.pclk1 = g_stm32f1_clocks.hclk;

  /* This default value means TCLK1 = 2 * PCLK1 (16 MHz, max ?? MHz) */
  g_stm32f1_clocks.tclk1 = g_stm32f1_clocks.pclk1 * 2;

  /* page 101 APB2 default prescaler = 1 (8 MHz, max 72 MHz) */
  g_stm32f1_clocks.pclk2 = g_stm32f1_clocks.hclk;
  
  /* This default value means TCLK2 = 2 * PCLK2 (16 MHz, max ?? MHz) */
  g_stm32f1_clocks.tclk2 = g_stm32f1_clocks.pclk2 * 2;

  /* page 101 ADC default prescaler = 2 (4 MHz, max 14 MHz) */
  g_stm32f1_clocks.adcclk = g_stm32f1_clocks.pclk2 / 2;

}

/*----------------------------------------------------------------------------*/
struct stm32f1_clocks_s * stm32f1_clock_getinfo(void)
{
  return &g_stm32f1_clocks;
}

/*----------------------------------------------------------------------------*/
void stm32f1_ahbprescaler(uint32_t prescaler)
{
}

/*----------------------------------------------------------------------------*/
void stm32f1_apb1prescaler(uint32_t prescaler)
{
}

/*----------------------------------------------------------------------------*/
void stm32f1_apb2prescaler(uint32_t prescaler)
{
}

/*----------------------------------------------------------------------------*/
void stm32f1_adcprescaler(uint32_t prescaler)
{
}

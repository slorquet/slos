#include <config.h>
#include <stdint.h>
#include <stdbool.h>

#include "armv7m.h"
#include "bits/stm32f1_periphs.h"
#include "bits/stm32f1_rcc.h"
#include "bits/stm32f1_rtc.h"
#include "stm32f1_rtc.h"

/*==============================================================================
 * Definitions
 *==============================================================================
 */

/*==============================================================================
 * Types
 *==============================================================================
 */

/*==============================================================================
 * Function Prototypes
 *==============================================================================
 */

/*==============================================================================
 * Variables and constants
 *==============================================================================
 */

/*==============================================================================
 * Functions
 *==============================================================================
 */

/*----------------------------------------------------------------------------*/
/* Enable the RTC. Clock source is supposed enabled */
bool stm32f1_rtc_init(uint32_t prescaler)
{
  uint32_t val;
  int tries = 1000;

  /* Enable BKP and PWR for RTC access */

  stm32f1_clock_enablebkp();

  /* Enable the RTC */

  val = getreg32(STM32F1_REGBASE_RCC + STM32F1_RCC_BDCR);
  val |= RCC_BDCR_RTCEN;
  putreg32(STM32F1_REGBASE_RCC + STM32F1_RCC_BDCR, val);

  /* Start Configuration */

  val = getreg32(STM32F1_REGBASE_RTC + STM32F1_RTC_CRL);
  val |= RTC_CRL_CNF;
  putreg32(STM32F1_REGBASE_RTC + STM32F1_RTC_CRL, val);

  /* Wait for RTOFF to be set */
  while(tries > 0)
    {
      val = getreg32(STM32F1_REGBASE_RTC + STM32F1_RTC_CRL);
      if (val & RTC_CRL_RTOFF) goto done;
      tries -= 1;
    }

  /* Timeout */
  return false;

done:
  /* Define the prescaler */

  putreg32(STM32F1_REGBASE_RTC + STM32F1_RTC_PRLH, prescaler >> 16   );
  putreg32(STM32F1_REGBASE_RTC + STM32F1_RTC_PRLL, prescaler & 0xFFFF);

  /* End Configuration */

  val = getreg32(STM32F1_REGBASE_RTC + STM32F1_RTC_CRL);
  val &= ~RTC_CRL_CNF;
  putreg32(STM32F1_REGBASE_RTC + STM32F1_RTC_CRL, val);

  return true;
}

/*----------------------------------------------------------------------------*/
/* Return the 32-bit RTC value read from the two 16-bit regs */
uint32_t stm32f1_rtc_read(void)
{
  /* Read the HI register, then LOW */

  uint32_t hi = getreg32(STM32F1_REGBASE_RTC + STM32F1_RTC_CNTH);
  uint32_t lo = getreg32(STM32F1_REGBASE_RTC + STM32F1_RTC_CNTL);

  /* Read high again */
  uint32_t h2 = getreg32(STM32F1_REGBASE_RTC + STM32F1_RTC_CNTH);

  /* If HIGH register did not change, then LOW register is still ok */
  if(h2 != hi)
    {
      /* Else, the LOW reg has to be read again */
      lo = getreg32(STM32F1_REGBASE_RTC + STM32F1_RTC_CNTL);
    }

  return (hi<<16) + lo;
}


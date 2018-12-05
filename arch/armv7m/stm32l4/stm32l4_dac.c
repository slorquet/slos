#include <stddef.h>
#include <stdint.h>
#include <errno.h>

#include "config.h"
#include "armv7m.h"
#include "stm32l4_gpio.h"
#include "stm32l4_dac.h"
#include "bits/stm32l4_rcc.h"
#include "bits/stm32l4_periphs.h"
#include "bits/stm32l4_dac.h"

#ifndef CONFIG_STM32L4_DAC1
#error this file should not be compiled if DAC1 support is not enabled
#endif

/*==============================================================================
 * Types
 *==============================================================================
 */

struct stm32l4_dacparams_s /* Stored in Flash */
{
  uint32_t base;
  uint32_t ckenreg;
  uint32_t ckenbit;
};

struct stm32l4_dac_s /* Stored in RAM */
{
  const struct stm32l4_dacops_s    *ops;
  const struct stm32l4_dacparams_s *params;
};

/*==============================================================================
 * Function Prototypes
 *==============================================================================
 */

static int stm32l4_dac_write(struct stm32l4_dac_s *dev, uint16_t channel, uint16_t value);
static int stm32l4_dac_trig (struct stm32l4_dac_s *dev, uint16_t chanmap);

/*==============================================================================
 * Variables and constants
 *==============================================================================
 */

static const struct stm32l4_dacops_s g_stm32l4_dacops =
{
  .write = stm32l4_dac_write,
  .trig  = stm32l4_dac_trig,
};

static const struct stm32l4_dacparams_s g_stm32l4_dac1params =
{
  .base    = STM32L4_REGBASE_DAC1,
  .ckenreg = STM32L4_RCC_APB1ENR1,
  .ckenbit = RCC_APB1ENR1_DAC1EN,
};

static struct stm32l4_dac_s g_stm32l4_dac1 =
{
  .ops    = &g_stm32l4_dacops,
  .params = &g_stm32l4_dac1params,
};

/*----------------------------------------------------------------------------*/
static inline uint32_t stm32l4_dac_getreg(const struct stm32l4_dac_s *dac, uint32_t regoff)
{
  return getreg32(dac->params->base + regoff);
}

/*----------------------------------------------------------------------------*/
static inline void stm32l4_dac_putreg(const struct stm32l4_dac_s *dac, uint32_t regoff, uint32_t value)
{
  putreg32(dac->params->base + regoff, value);
}

/*----------------------------------------------------------------------------*/
static inline void stm32l4_dac_updatereg(const struct stm32l4_dac_s *dac, uint32_t regoff, uint32_t setbits, uint32_t clrbits)
{
  updatereg32(dac->params->base + regoff, setbits, clrbits);
}

/*----------------------------------------------------------------------------*/
static int stm32l4_dac_write(struct stm32l4_dac_s *dev, uint16_t channel, uint16_t value)
{
  int i;
  int ret = 0;
  struct stm32l4_dac_s *dac = (struct stm32l4_dac_s *)dev;

  return ret;
}

/*----------------------------------------------------------------------------*/
static int stm32l4_dac_trig(struct stm32l4_dac_s *dev, uint16_t chanmap)
{
  int i;
  int ret = 0;
  struct stm32l4_dac_s *dac = (struct stm32l4_dac_s *)dev;

  return ret;
}

/*----------------------------------------------------------------------------*/
struct stm32l4_dac_s *stm32l4_dac_init(uint32_t dacid, bool ch1en, bool ch2en)
{
  struct stm32l4_dac_s *dac;

  if(dacid != 1)
    {
      return NULL;
    }

  dac = &g_stm32l4_dac1;

  /* Configure GPIOs */

   //stm32l4_gpio_init(dac->params->sclkpin);

  /* Enable clock to DAC peripheral */

  updatereg32(STM32L4_REGBASE_RCC + dac->params->ckenreg, dac->params->ckenbit, 0);

  /* Return instance */
  return dac;
}


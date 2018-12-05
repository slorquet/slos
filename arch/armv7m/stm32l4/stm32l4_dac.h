#ifndef _ARCH_ARMV7M_STM32L4_STM32L4_DAC_H_
#define _ARCH_ARMV7M_STM32L4_STM32L4_DAC_H_

#include <stdint.h>
#include <stdbool.h>


/*==============================================================================
 * Definitions
 *==============================================================================
 */

#define STM32L4_DAC_WRITE(dev, ch, val) dev->ops->write(dev, ch, val)
#define STM32L4_DAC_TRIG (dev, chmap)   dev->ops->write(dev, chmap)

/*==============================================================================
 * Types
 *==============================================================================
 */

struct stm32l4_dac_s;

struct stm32l4_dacops_s
{
  int (*write)(struct stm32l4_dac_s *dac, uint16_t channel, uint16_t value);
  int (*trig) (struct stm32l4_dac_s *dac, uint16_t chanmap);
};

/*==============================================================================
 * Public functions
 *==============================================================================
 */

/* init registers before operations */

struct stm32l4_dac_s * stm32l4_dac_init(uint32_t dacid, bool ch1en, bool ch2en);

#endif // __STM32__DAC__H__


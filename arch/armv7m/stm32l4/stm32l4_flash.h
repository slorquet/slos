#ifndef _ARCH_ARMV7M_STM32L4_STM32L4_FLASH_H_
#define _ARCH_ARMV7M_STM32L4_STM32L4_FLASH_H_

#include <stdint.h>
#include <stdbool.h>


/*==============================================================================
 * Definitions
 *==============================================================================
 */

#define STM32L4_ERASE_SIZE 2048

/*==============================================================================
 * Types
 *==============================================================================
 */

struct stm32l4_devicesig_s
{
  uint16_t flashsize;
  uint8_t  package;
  uint8_t  waf_num;   /* Wafer number */
  uint16_t waf_x;     /* Die X coordnate in wafer */
  uint16_t waf_y;     /* Die Y coordinate in wafer */
  uint8_t  lotnum[8]; /* Lot number, ASCII with final 0 */
};

/*==============================================================================
 * Public functions
 *==============================================================================
 */

/* init registers before operations */

void stm32l4_flash_init(void);

void stm32l4_flash_getdevicesig(struct stm32l4_devicesig_s *sig);

/* erase flash at any address, return erased size or zero if error */

bool stm32l4_flash_erase(uint32_t destaddr);

/* write some data to the flash */

bool stm32l4_flash_write(uint32_t destaddr, uint8_t *sourcedata, uint32_t len);

#endif // __STM32__FLASH__H__


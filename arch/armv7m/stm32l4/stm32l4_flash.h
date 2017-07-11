#ifndef _ARCH_ARMV7M_STM32L4_STM32L4_FLASH_H_
#define _ARCH_ARMV7M_STM32L4_STM32L4_FLASH_H_

#include <stdint.h>

struct stm32l4_device_sig_s
{
  uint8_t  waf_num; /* Wafer number */
  uint16_t waf_x;   /* Die X coordnate in wafer */
  uint16_t waf_y;   /* Die Y coordinate in wafer */
  uint8_t  lotnum[7]; /* Lot number */
};

/* init registers before operations*/

void stm32_flash_init(uint8_t blocksize);

/* erase flash at any address, return erased size */

uint32_t stm32_flash_erase(uint32_t destaddr);

/* write some data to the flash */

int stm32_flash_write(uint32_t destaddr, uint8_t *sourcedata, uint32_t len);

#endif // __STM32__FLASH__H__


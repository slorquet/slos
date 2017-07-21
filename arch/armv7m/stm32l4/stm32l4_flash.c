#include <stdint.h>
#include <stdbool.h>

#include "armv7m.h"
#include "stm32l4.h"
#include "bits/stm32l4_periphs.h"
#include "bits/stm32l4_flash.h"
#include "stm32l4_flash.h"

/* the stm32l4 flash is made of 2KB blocks
 * checked for 32l4x6 and 23l4x2
 8 programming is done 64 bits at a time
 */

/*==============================================================================
 * Variables and constants
 *==============================================================================
 */

static uint32_t sectcount;

/*==============================================================================
 * Functions
 *==============================================================================
 */

/*----------------------------------------------------------------------------*/
static inline void stm32l4_flash_putreg(uint32_t regoff, uint32_t value)
{
  putreg32(STM32L4_REGBASE_FLASH + regoff, value);
}

/*----------------------------------------------------------------------------*/
static inline uint32_t stm32l4_flash_getreg(uint32_t regoff)
{
  return getreg32(STM32L4_REGBASE_FLASH + regoff);
}

/*----------------------------------------------------------------------------*/
static inline void stm32l4_flash_updatereg(uint32_t regoff, uint32_t set, uint32_t clr)
{
  updatereg32(STM32L4_REGBASE_FLASH + regoff, set, clr);
}

/*----------------------------------------------------------------------------*/
void stm32l4_flash_init(void)
{
  /* Disable the dual bank feature if available */

#if defined(CONFIG_ARCH_CHIPFAMILY_STM32L4X6)
  stm32l4_flash_putreg(STM32L4_FLASH_OPTKEYR, 0x08192A3B);
  stm32l4_flash_putreg(STM32L4_FLASH_OPTKEYR, 0x4C5D6E7F); /* unlock */

  stm32l4_flash_updatereg(STM32L4_FLASH_OPTR, 0, FLASH_OPTCR_DUALBANK)i;

  stm32l4_flash_updatereg(STM32L4_FLASH_CR, FLASH_OPTCR_OPTLOCK, 0); /* relock */

#endif

  /* read flash info and define sector count */

  sectcount = getreg32(STM32L4_REGBASE_SYSFLASH + STM32L4_SYSFLASH_SIZE) & SYSFLASH_SIZE_MASK;
  sectcount >>= 1; /* sectors are 2k */
}

/*----------------------------------------------------------------------------*/
/* Return the address of the end of flash */
uint32_t stm32l4_flash_end(void)
{
  return STM32L4_REGBASE_USRFLASH + (sectcount<<11);
}

/*----------------------------------------------------------------------------*/
/* Wait until the flash is not busy anymore. do that only for a limited time.
 * If flash is still busy after timeout, return false.
 */
static bool stm32l4_flash_waitnotbusy(void)
{
  while(stm32l4_flash_getreg(STM32L4_FLASH_SR) & FLASH_SR_BSY);
  return true;
}

/*----------------------------------------------------------------------------*/
bool stm32l4_flash_erase(uint32_t destaddr)
{
  int sect;
  uint32_t base = STM32L4_REGBASE_USRFLASH;

  /* check for busy */
  if (!stm32l4_flash_waitnotbusy())
    {
      return false; //timeout
    }

  /*find sector*/

  if (destaddr < base)
    {
      return false;
    }
  sect = (destaddr - base) >> 11;
  if (sect >= sectcount)
    {
      return false;
    }

  /* unlock */

  stm32l4_flash_putreg(STM32L4_FLASH_KEYR, 0x45670123);
  stm32l4_flash_putreg(STM32L4_FLASH_KEYR, 0xCDEF89AB);

  /*set PER*/

  stm32l4_flash_updatereg(STM32L4_FLASH_CR, FLASH_CR_PER, 0);

  /* set sector index to erase*/

  stm32l4_flash_updatereg(STM32L4_FLASH_CR, sect<<FLASH_CR_PNB_SHIFT, FLASH_CR_PNB_MASK);
    
  /*set START*/

  stm32l4_flash_updatereg(STM32L4_FLASH_CR, FLASH_CR_STRT, 0);

  /* wait for completion */

  if (!stm32l4_flash_waitnotbusy())
    {
      return false; //timeout
    }
  
  /* Relock */

  stm32l4_flash_updatereg(STM32L4_FLASH_CR, FLASH_CR_LOCK, 0);

  return true;
}

/*----------------------------------------------------------------------------*/
bool stm32l4_flash_write(uint32_t destaddr, uint8_t *sourcedata, uint32_t len)
{
  /* retrieve current write element size from CR */
  uint32_t offset;

  /* check that memory to write has the correct size */

  if ((len & 7))
    {
    return false;
    }

  /* unlock */

  stm32l4_flash_putreg(STM32L4_FLASH_KEYR, 0x45670123);
  stm32l4_flash_putreg(STM32L4_FLASH_KEYR, 0xCDEF89AB);

  /* program */

  for (offset = 0; offset < len; offset += 8)
    {
      stm32l4_flash_updatereg(STM32L4_FLASH_CR, FLASH_CR_PG, FLASH_CR_PER);

      *((volatile uint32_t*)destaddr) = *(uint32_t*)sourcedata;
      sourcedata += 4;
      destaddr   += 4;
      *((volatile uint32_t*)destaddr) = *(uint32_t*)sourcedata;
      sourcedata += 4;
      destaddr   += 4;

      /* wait for completion */

      if ( !stm32l4_flash_waitnotbusy() )
        {
          return false; //timeout
        }
  
      /* Check for errors */
#warning TODO check programming errors

      /* next block */
    }

  /* Relock */

  stm32l4_flash_updatereg(STM32L4_FLASH_CR, FLASH_CR_LOCK, 0);

  return true; /*success*/
}


void stm32l4_flash_getdevicesig(struct stm32l4_devicesig_s *sig)
{
  uint32_t id;

  id = getreg32(STM32L4_REGBASE_SYSFLASH + STM32L4_SYSFLASH_UID0);
  sig->waf_x = (id & SYSFLASH_UID0_X_MASK) >> SYSFLASH_UID0_X_SHIFT;
  sig->waf_y = (id & SYSFLASH_UID0_Y_MASK) >> SYSFLASH_UID0_Y_SHIFT;

  id = getreg32(STM32L4_REGBASE_SYSFLASH + STM32L4_SYSFLASH_UID1);
  sig->waf_num = (id & SYSFLASH_UID1_WAFNUM_MASK) >> SYSFLASH_UID1_WAFNUM_SHIFT;
  sig->lotnum[4] = (id >> 24) & 0xFF;
  sig->lotnum[5] = (id >> 16) & 0xFF;
  sig->lotnum[6] = (id >>  8) & 0xFF;

  id = getreg32(STM32L4_REGBASE_SYSFLASH + STM32L4_SYSFLASH_UID2);
  sig->lotnum[0] = (id >> 24) & 0xFF;
  sig->lotnum[1] = (id >> 16) & 0xFF;
  sig->lotnum[2] = (id >>  8) & 0xFF;
  sig->lotnum[3] =  id        & 0xFF;
  sig->lotnum[7] = 0;

  sig->flashsize = getreg32(STM32L4_REGBASE_SYSFLASH + STM32L4_SYSFLASH_SIZE) & SYSFLASH_SIZE_MASK;
  sig->package   = getreg32(STM32L4_REGBASE_SYSFLASH + STM32L4_SYSFLASH_UID0) & SYSFLASH_PACKAGE_MASK;
}


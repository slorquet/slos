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
 * Definitions
 *==============================================================================
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
void stm32l4_flash_init(void)
{
  uint32_t reg;

#if defined(CONFIG_ARCH_CHIPFAMILY_STM32L4X6)
  putreg32(STM32L4_FLASH_OPTKEYR, 0x08192A3B);
  putreg32(STM32L4_FLASH_OPTKEYR, 0x4C5D6E7F); /* unlock */

  reg = getreg32(STM32L4_FLASH_OPTCR);
  reg &= ~STM32L4_FLASH_OPTCR_DUALBANK;
  reg |=  STM32L4_FLASH_OPTCR_OPTLOCK; /* relock */
  putreg32(STM32L4_FLASH_OPTCR, reg);
#endif

  /* unlock */
  putreg32(STM32L4_FLASH_KEYR, 0x45670123);
  putreg32(STM32L4_FLASH_KEYR, 0xCDEF89AB);

  /* set block size */
  blocksize &= 3; /* only keep 2 bits */
  reg = getreg32(STM32L4_FLASH_CR);
  reg &= ~0x00000300;
  reg |= blocksize<<8;
  putreg32(STM32L4_FLASH_CR, reg);

  /* Relock */
  reg |= STM32L4_FLASH_CR_LOCK;
  putreg32(STM32L4_FLASH_CR, reg);

  /* read flash info and define sector count */
  sectcount = getreg16(STM32L4_REGBASE_SYSFLASH + iSTM32L4_SYSFLASH_SIZE);

  switch(sectcount)
    {
      case 0x200: sectcount =  8; break;
      case 0x400: sectcount = 12; break;
      case 0x800: sectcount = 24; break;
      default: sectcount = 0;
   }
}

/*----------------------------------------------------------------------------*/
/* Wait until the flash is not busy anymore. do that only for a limited time.
 * If flash is still busy after timeout, return false.
 */
static bool stm32l4_stm32l4_flash_waitnotbusy(void)
{
  while(getreg32(STM32L4_FLASH_SR) & STM32L4_FLASH_SR_BSY);
  return true;
}

/*----------------------------------------------------------------------------*/
bool stm32l4_flash_erase(uint32_t destaddr)
{
  int i;
  uint32_t addr = STM32L4_FLASH_BASE;
  uint32_t reg;

  /* check for busy */
  if ( !stm32l4_flash_waitnotbusy() )
    {
      return false; //timeout
    }

  /*find sector*/
  for(i = 0; i < sectcount; i++)
    {
      if(addr == destaddr)
        {
          break;
        } else if(addr > destaddr) {
          return 0; //not a sector begin addr
        }
      addr += (sectors_kb[i]<<10);
    }
  if(i == sectcount)
    {
      /* searched all without finding */
      return 0;
    }

  /* okay, erase */

  /* unlock */
  putreg32(STM32L4_FLASH_KEYR, 0x45670123);
  putreg32(STM32L4_FLASH_KEYR, 0xCDEF89AB);

  /*set SER*/
  reg = getreg32(STM32L4_FLASH_CR);
  reg |= STM32L4_FLASH_CR_SER;
  putreg32(STM32L4_FLASH_CR, reg);

  /* set sector index */
  reg &= ~(0x1F << 3);
  reg |=  (i    << 3);
  putreg32(STM32L4_FLASH_CR, reg);
    
  /*set START*/
  reg |= STM32L4_FLASH_CR_START;
  putreg32(STM32L4_FLASH_CR, reg);

  /* wait for completion */
  if ( !stm32l4_flash_waitnotbusy() )
    {
      return false; //timeout
    }
  
  /* Relock */
  reg |= STM32L4_FLASH_CR_LOCK;
  putreg32(STM32L4_FLASH_CR, reg);

  /* Return KB in this sector */
  return true;
}

/*----------------------------------------------------------------------------*/
bool stm32l4_flash_write(uint32_t destaddr, uint8_t *sourcedata, uint32_t len)
{
  /* retrieve current write element size from CR */
  uint32_t offset;
  uint32_t reg;

  /* check that memory to write has the correct size */

  if( (len & 7) )
    {
    return false;
    }

  /* unlock */

  putreg32(STM32L4_FLASH_KEYR, 0x45670123);
  putreg32(STM32L4_FLASH_KEYR, 0xCDEF89AB);

  /* program */

  for(offset = 0; offset < len; offset += blocksize)
    {
      reg = getreg32(STM32L4_FLASH_CR);
      reg &= ~STM32L4_FLASH_CR_SER;
      reg |= STM32L4_FLASH_CR_PG;
      putreg32(STM32L4_FLASH_CR, reg);

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

  reg |= STM32L4_FLASH_CR_LOCK;
  putreg32(STM32L4_FLASH_CR, reg);

  return true; /*success*/
}


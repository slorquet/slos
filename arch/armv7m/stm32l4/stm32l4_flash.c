#include <stdint.h>

#include "armv7m.h"
#include "stm32l4.h"
#include "stm32l4_flash.h"

/* Even for 2MB parts we dont use the dual bank feature */

static const uint32_t sectors_kb[] = {
  /* 512 K */

  16,  /*  0 */
  16,  /*  1 */
  16,  /*  2 */
  16,  /*  3 */
  64,  /*  4 */
  128, /*  5 */
  128, /*  6 */
  128, /*  7 */

  /* 1024 K */

  128, /*  8 */
  128, /*  9 */
  128, /* 10 */
  128,  /* 11 */

  /* 2048 K */

  16,  /* 12 */
  16,  /* 13 */
  16,  /* 14 */
  16,  /* 15 */
  64,  /* 16 */
  128, /* 17 */
  128, /* 18 */
  128, /* 19 */
  128, /* 20 */
  128, /* 21 */
  128, /* 23 */
  128  /* 23 */
};

static uint32_t sectcount;

void stm32_flash_init(uint8_t blocksize)
{
#if STM32_CORE == STM32F427 || STM32F429 || STM32F437 || STM32F439
  uint32_t reg;

  putreg32(STM32_FLASH_OPTKEYR, 0x08192A3B);
  putreg32(STM32_FLASH_OPTKEYR, 0x4C5D6E7F); /* unlock */

  reg = getreg32(STM32_FLASH_OPTCR);
  reg &= ~STM32_FLASH_OPTCR_DB1M;
  reg |=  STM32_FLASH_OPTCR_OPTLOCK; /* relock */
  putreg32(STM32_FLASH_OPTCR, reg);
#endif

  /* unlock */
  putreg32(STM32_FLASH_KEYR, 0x45670123);
  putreg32(STM32_FLASH_KEYR, 0xCDEF89AB);

  /* set block size */
  blocksize &= 3; /* only keep 2 bits */
  reg = getreg32(STM32_FLASH_CR);
  reg &= ~0x00000300;
  reg |= blocksize<<8;
  putreg32(STM32_FLASH_CR, reg);

  /* Relock */
  reg |= STM32_FLASH_CR_LOCK;
  putreg32(STM32_FLASH_CR, reg);

  /* read flash info and define sector count */
  sectcount = getreg16(STM32_FLASH_SIZE_ADDR);

  switch(sectcount)
    {
      case 0x200: sectcount =  8; break;
      case 0x400: sectcount = 12; break;
      case 0x800: sectcount = 24; break;
      default: sectcount = 0;
   }
}

uint32_t stm32_flash_erase(uint32_t destaddr)
{
  int i;
  uint32_t addr = STM32_FLASH_BASE;
  uint32_t reg;

  /* check for busy */
  if( getreg32(STM32_FLASH_SR) & STM32_FLASH_SR_BSY)
    {
      return 0;
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
  putreg32(STM32_FLASH_KEYR, 0x45670123);
  putreg32(STM32_FLASH_KEYR, 0xCDEF89AB);

  /*set SER*/
  reg = getreg32(STM32_FLASH_CR);
  reg |= STM32_FLASH_CR_SER;
  putreg32(STM32_FLASH_CR, reg);

  /* set sector index */
  reg &= ~(0x1F << 3);
  reg |=  (i    << 3);
  putreg32(STM32_FLASH_CR, reg);
    
  /*set START*/
  reg |= STM32_FLASH_CR_START;
  putreg32(STM32_FLASH_CR, reg);

  /* wait for completion */
  while(getreg32(STM32_FLASH_SR) & STM32_FLASH_SR_BSY);

  /* Relock */
  reg |= STM32_FLASH_CR_LOCK;
  putreg32(STM32_FLASH_CR, reg);

  /* Return KB in this sector */
  return (sectors_kb[i]<<10);
}

int stm32_flash_write(uint32_t destaddr, uint8_t *sourcedata, uint32_t len)
{
  /* retrieve current write element size from CR */
  uint32_t blocksize = (getreg32(STM32_FLASH_CR)>>8) & 0x03;
  uint32_t offset;
  uint32_t reg;

  blocksize = 1 << blocksize;

  /* check that memory to write has the correct size */
  if( (len & (blocksize-1))!=0)
    {
    return 1;
    }

  /* unlock */
  putreg32(STM32_FLASH_KEYR, 0x45670123);
  putreg32(STM32_FLASH_KEYR, 0xCDEF89AB);

  /* program */

  for(offset = 0; offset < len; offset += blocksize)
    {
      reg = getreg32(STM32_FLASH_CR);
      reg &= ~STM32_FLASH_CR_SER;
      reg |= STM32_FLASH_CR_PG;
      putreg32(STM32_FLASH_CR, reg);

      switch(blocksize)
        {
        case 1: /* 8-bit writes */
          *((volatile uint8_t*)destaddr) = *sourcedata;
          break;

        case 2: /* 16-bit writes */
          *((volatile uint16_t*)destaddr) = *(uint16_t*)sourcedata;
          break;

        case 4: /* 32-bit writes */
          *((volatile uint32_t*)destaddr) = *(uint32_t*)sourcedata;
          break;

        case 8: /* 64-bit writes */
          *((volatile uint64_t*)destaddr) = *(uint64_t*)sourcedata;
          break;

        default:
          return 1; /*error*/
        }

      /* wait for completion */
      while(getreg32(STM32_FLASH_SR) & STM32_FLASH_SR_BSY);

      /* next block */
      sourcedata += blocksize;
      destaddr   += blocksize;
    }

  /* Relock */
  /* Relock */
  reg |= STM32_FLASH_CR_LOCK;
  putreg32(STM32_FLASH_CR, reg);

  return 0; /*success*/
}


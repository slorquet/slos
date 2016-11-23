#ifndef __STM32__FLASH__H__
#define __STM32__FLASH__H__

enum {
    FLASH_BLOCK_8,
    FLASH_BLOCK_16,
    FLASH_BLOCK_32,
    FLASH_BLOCK_64
};

#define STM32_FLASH_BASE          0x08000000

#define STM32_FLASH_SIZE_ADDR     0x1FFF7A22

#define STM32_FLASH_KEYR          0x40023C04
#define STM32_FLASH_OPTKEYR       0x40023C08
#define STM32_FLASH_SR            0x40023C0C
#define STM32_FLASH_CR            0x40023C10
#define STM32_FLASH_OPTCR         0x40023C14

#define STM32_FLASH_CR_PG         (1<<  0)
#define STM32_FLASH_CR_SER        (1<<  1)
#define STM32_FLASH_CR_START      (1<< 16)
#define STM32_FLASH_CR_LOCK       (1<< 31)

#define STM32_FLASH_SR_BSY        (1<< 16)

#define STM32_FLASH_OPTCR_OPTLOCK (1<<  0)
#define STM32_FLASH_OPTCR_DB1M    (1<< 30)

/* init registers before operations*/

void stm32_flash_init(uint8_t blocksize);

/* erase flash at any address, return erased size */

uint32_t stm32_flash_erase(uint32_t destaddr);

/* write some data to the flash */

int stm32_flash_write(uint32_t destaddr, uint8_t *sourcedata, uint32_t len);

#endif // __STM32__FLASH__H__


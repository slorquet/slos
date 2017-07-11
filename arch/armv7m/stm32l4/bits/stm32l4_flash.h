#ifndef _ARCH_ARMV7M_STM32L4_BITS_STM32L4_FLASH_H_
#define _ARCH_ARMV7M_STM32L4_BITS_STM32L4_FLASH_H_

enum {
    FLASH_BLOCK_8,
    FLASH_BLOCK_16,
    FLASH_BLOCK_32,
    FLASH_BLOCK_64
};

/* Device electronic signature registers,
 * relative to STM32L4_REGBASE_SYSFLASH
 */

#define STM32L4_SYSFLASH_PACKAGE    0x7500 /* Contains package ID */
#define STM32L4_SYSFLASH_UID0       0x7590 /* Contains XY coords in wafer */
#define STM32L4_SYSFLASH_UID1       0x7594 /* Contains Lot num and wafer num */
#define STM32L4_SYSFLASH_UID2       0x7598 /* Contains Lot num */
#define STM32L4_SYSFLASH_SIZE       0x75E0 /* Slash size in Kbytes */

#define SYSFLASH_PACKAGE_MASK         0x1F
#define SYSFLASH_PACKAGE_LQFP64       0
#define SYSFLASH_PACKAGE_WLCSP64      1
#define SYSFLASH_PACKAGE_LQFP100      2
#define SYSFLASH_PACKAGE_UFBGA132     3
#define SYSFLASH_PACKAGE_LQFP144WLCSP 4
#define SYSFLASH_PACKAGE_UFQFPN48     10
#define SYSFLASH_PACKAGE_LQFP48       11
#define SYSFLASH_PACKAGE_WLCSP49      12
#define SYSFLASH_PACKAGE_UFBGA64      13
#define SYSFLASH_PACKAGE_UFBGA100     14

#define SYSFLASH_SIZE_MASK            0xFFFF

#define SYSFLASH_UID0_X_SHIFT         16
#define SYSFLASH_UID0_X_MASK          (0xFFFF << SYSFLASH_UID0_X_SHIFT)
#define SYSFLASH_UID0_Y_SHIFT         0
#define SYSFLASH_UID0_Y_MASK          (0xFFFF << SYSFLASH_UID0_Y_SHIFT)
#define SYSFLASH_UID1_LOT_SHIFT       8
#define SYSFLASH_UID1_LOT_MASK        (0xFFFFFF << SYSFLASH_UID1_LOT_SHIFT)
#define SYSFLASH_UID1_WAFNUM_SHIFT    0
#define SYSFLASH_UID1_WAFNUM_MASK     (0xFF << SYSFLASH_UID1_WAFNUM_SHIFT)

/* Flash controller registers */

#define STM32L4_FLASH_ACR           0x000
#define STM32L4_FLASH_PDKEYR        0x004
#define STM32L4_FLASH_KEYR          0x008
#define STM32L4_FLASH_OPTKEYR       0x00C
#define STM32L4_FLASH_SR            0x010
#define STM32L4_FLASH_CR            0x014
#define STM32L4_FLASH_ECCR          0x018
#define STM32L4_FLASH_OPTCR         0x020
#define STM32L4_FLASH_PCROP1SR      0x024
#define STM32L4_FLASH_PCROP1ER      0x028
#define STM32L4_FLASH_WRP1AR        0x02C
#define STM32L4_FLASH_WRP1BR        0x030

#if defined(CONFIG_ARCH_CHIPFAMILY_STM32L4X6)
/* Additional regs for 4x6 dual bank */
#define STM32L4_FLASH_PCROP2SR      0x044
#define STM32L4_FLASH_PCROP2ER      0x048
#define STM32L4_FLASH_WRP2AR        0x04C
#define STM32L4_FLASH_WRP2BR        0x050
#endif
#define STM32_FLASH_CR_PG           (1<<  0)
#define STM32_FLASH_CR_SER          (1<<  1)
#define STM32_FLASH_CR_START        (1<< 16)
#define STM32_FLASH_CR_LOCK         (1<< 31)

#define STM32_FLASH_SR_BSY          (1<< 16)

#define STM32_FLASH_OPTCR_OPTLOCK   (1<<  0)
#define STM32_FLASH_OPTCR_DUALBANK  (1<< 21)

#endif // _ARCH_ARMV7M_STM32L4_BITS_STM32L4_FLASH_H_


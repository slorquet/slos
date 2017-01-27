#ifndef __ARCH__ARMV6M__STM32F1__BITS__STM32F1__PWR__H__
#define __ARCH__ARMV6M__STM32F1__BITS__STM32F1__PWR__H__

#define STM32F1_PWR_CR       0x00 /* Control register */
#define STM32F1_PWR_CSR      0x04 /* Control/Status register */

/* Control Register */

#define PWR_CR_LPDS      (1<<0) /* Low-power deepsleep */
#define PWR_CR_PPDS      (1<<1) /* Power down deepsleep */
#define PWR_CR_CWUF      (1<<2) /* Clear wakeup Flag */
#define PWR_CR_CSBF      (1<<3) /* Clear standby Flag */
#define PWR_CR_PVDE      (1<<4) /* Power voltage detector enable */
#define PWR_CR_PLS_SHIFT 5
#define PWR_CR_PLS_MASK  (7<<PWR_CR_PLS_SHIFT) /* PVD level in 100mv steps from 2.2V */
#define PWR_CR_DBP       (1<<8) /* Disable Backup Domain Write Protection */

/* Control/Status Register */

#define PWR_CSR_WUF  (1<<0) /* Enable WKUP pin */
#define PWR_CSR_SBF  (1<<1) /* Standby Flag */
#define PWR_CSR_PVDO (1<<2) /* PDV output */
#define PWR_CSR_EWUP (1<<8) /* Wakeup Flag */

#endif /* __ARCH__ARMV6M__STM32F1__BITS__STM32F1__PWR__H__ */

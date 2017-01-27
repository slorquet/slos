#ifndef __ARCH__ARMV7M__STM32F1__BITS__STM32F1__RTC__H__
#define __ARCH__ARMV7M__STM32F1__BITS__STM32F1__RTC__H__

/* RTC Register offsets */

#define STM32F1_RTC_CRH    0x00
#define STM32F1_RTC_CRL    0x04
#define STM32F1_RTC_PRLH   0x08
#define STM32F1_RTC_PRLL   0x0C
#define STM32F1_RTC_DIVH   0x10
#define STM32F1_RTC_DIVL   0x14
#define STM32F1_RTC_CNTH   0x18
#define STM32F1_RTC_CNTL   0x1C
#define STM32F1_RTC_ALRH   0x20
#define STM32F1_RTC_ALRL   0x24

/* Control Register High */

#define RTC_CRH_SECIE (1<<0) /* Second interrupt enable */
#define RTC_CRH_ALRIE (1<<1) /* Alarm interrupt enable */
#define RTC_CRH_OWIE  (1<<2) /* Overflow interrupt enable */

/* Control Register Low */

#define RTC_CRL_SECF  (1<<0) /* Second flag */
#define RTC_CRL_ALRF  (1<<1) /* Alarm flag */
#define RTC_CRL_OWF   (1<<2) /* Overflow flag */
#define RTC_CRL_RSF   (1<<3) /* Registers Synchronized flags */
#define RTC_CRL_CNF   (1<<4) /* Configuration flag */
#define RTC_CRL_RTOFF (1<<5) /* RTC operation OFF */

#endif /* __ARCH__ARMV6M__STM32F1__BITS__STM32F1__RTC__H__ */

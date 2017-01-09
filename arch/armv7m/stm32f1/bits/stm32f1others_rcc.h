#ifndef __ARCH__ARMV6M__STM32F1__BITS__STM32F1OTHERS__RCC__H__
#define __ARCH__ARMV6M__STM32F1__BITS__STM32F1OTHERS__RCC__H__

#define STM32F1_RCC_CR       0x000 /* Clock Control register */
#define STM32F1_RCC_CFGR     0x004 /* Clock Configuration register */
#define STM32F1_RCC_CIR      0x008 /* Clock Interrupt register */
#define STM32F1_RCC_APB2RSTR 0x00C /* APB2 peripheral reset register */
#define STM32F1_RCC_APB1RSTR 0x010 /* APB1 peripheral reset register */
#define STM32F1_RCC_AHBENR   0x014 /* AHB  peripheral enable register */
#define STM32F1_RCC_APB2ENR  0x018 /* APB2 peripheral enable register */
#define STM32F1_RCC_APB1ENR  0x01C /* APB1 peripheral enable register */
#define STM32F1_RCC_BDCR     0x020 /* Backup Domain Control register */
#define STM32F1_RCC_CSR      0x024 /* Control/Status register */

/* RCC_CR bits */

#define RCC_CR_HSION         (1 <<  0)
#define RCC_CR_HSIRDY        (1 <<  1)
#define RCC_CR_HSITRIM_SHIFT 3
#define RCC_CR_HSITRIM_MASK  (0x1F << STM32F1_RCC_CR_HSITRIM_SHIFT)
#define RCC_CR_HSICAL_SHIFT  8
#define RCC_CR_HSICAL_MASK   (0xFF << STM32F1_RCC_CR_HSICAL_SHIFT)
#define RCC_CR_HSEON         (1 << 16)
#define RCC_CR_HSERDY        (1 << 17)
#define RCC_CR_HSEBYP        (1 << 18)
#define RCC_CR_CSSON         (1 << 19)
#define RCC_CR_PLLON         (1 << 24)
#define RCC_CR_PLLRDY        (1 << 25)

/* RCC_CFGR bits */

#define RCC_CFGR_SW_SHIFT     0
#define RCC_CFGR_SW_MASK      (3 << RCC_CFGR_SW_SHIFT)
#define RCC_CFGR_SW_HSI       (0 << RCC_CFGR_SW_SHIFT)
#define RCC_CFGR_SW_HSE       (1 << RCC_CFGR_SW_SHIFT)
#define RCC_CFGR_SW_PLLDIV2   (2 << RCC_CFGR_SW_SHIFT)

#define RCC_CFGR_SWS_SHIFT    2
#define RCC_CFGR_SWS_MASK     (3 << RCC_CFGR_SWS_SHIFT)
#define RCC_CFGR_SWS_HSI      (0 << RCC_CFGR_SWS_SHIFT)
#define RCC_CFGR_SWS_HSE      (1 << RCC_CFGR_SWS_SHIFT)
#define RCC_CFGR_SWS_PLL      (2 << RCC_CFGR_SWS_SHIFT)

#define RCC_CFGR_HPRE_SHIFT   4
#define RCC_CFGR_HPRE_MASK    (15 << RCC_CFGR_HPRE_SHIFT)
#define RCC_CFGR_HPRE_DIV1    ( 0 << RCC_CFGR_HPRE_SHIFT)
#define RCC_CFGR_HPRE_DIV2    ( 8 << RCC_CFGR_HPRE_SHIFT)
#define RCC_CFGR_HPRE_DIV4    ( 9 << RCC_CFGR_HPRE_SHIFT)
#define RCC_CFGR_HPRE_DIV8    (10 << RCC_CFGR_HPRE_SHIFT)
#define RCC_CFGR_HPRE_DIV16   (11 << RCC_CFGR_HPRE_SHIFT)
#define RCC_CFGR_HPRE_DIV64   (12 << RCC_CFGR_HPRE_SHIFT)
#define RCC_CFGR_HPRE_DIV128  (13 << RCC_CFGR_HPRE_SHIFT)
#define RCC_CFGR_HPRE_DIV256  (14 << RCC_CFGR_HPRE_SHIFT)
#define RCC_CFGR_HPRE_DIV512  (15 << RCC_CFGR_HPRE_SHIFT)

#define RCC_CFGR_PPRE1_SHIFT  8
#define RCC_CFGR_PPRE1_MASK   (7 << RCC_CFGR_PPRE1_SHIFT)
#define RCC_CFGR_PPRE1_DIV1   (0 << RCC_CFGR_PPRE1_SHIFT)
#define RCC_CFGR_PPRE1_DIV2   (4 << RCC_CFGR_PPRE1_SHIFT)
#define RCC_CFGR_PPRE1_DIV4   (5 << RCC_CFGR_PPRE1_SHIFT)
#define RCC_CFGR_PPRE1_DIV8   (6 << RCC_CFGR_PPRE1_SHIFT)
#define RCC_CFGR_PPRE1_DIV16  (7 << RCC_CFGR_PPRE1_SHIFT)

#define RCC_CFGR_PPRE2_SHIFT  11
#define RCC_CFGR_PPRE2_MASK   (7 << RCC_CFGR_PPRE2_SHIFT)
#define RCC_CFGR_PPRE2_DIV1   (0 << RCC_CFGR_PPRE2_SHIFT)
#define RCC_CFGR_PPRE2_DIV2   (4 << RCC_CFGR_PPRE2_SHIFT)
#define RCC_CFGR_PPRE2_DIV4   (5 << RCC_CFGR_PPRE2_SHIFT)
#define RCC_CFGR_PPRE2_DIV8   (6 << RCC_CFGR_PPRE2_SHIFT)
#define RCC_CFGR_PPRE2_DIV16  (7 << RCC_CFGR_PPRE2_SHIFT)

#define RCC_CFGR_ADCPRE_SHIFT 14
#define RCC_CFGR_ADCPRE_MASK  (3 << RCC_CFGR_ADCPRE_SHIFT)
#define RCC_CFGR_ADCPRE_DIV2  (0 << RCC_CFGR_ADCPRE_SHIFT)
#define RCC_CFGR_ADCPRE_DIV4  (1 << RCC_CFGR_ADCPRE_SHIFT)
#define RCC_CFGR_ADCPRE_DIV6  (2 << RCC_CFGR_ADCPRE_SHIFT)
#define RCC_CFGR_ADCPRE_DIV8  (3 << RCC_CFGR_ADCPRE_SHIFT)

#define RCC_CFGR_PLLSRC       (1 << 16)
#define RCC_CFGR_PLLXTPRE     (1 << 17)
#define RCC_CFGR_PLLMUL_SHIFT 18
#define RCC_CFGR_PLLMUL_MASK  (0x0F << STM32F1_RCC_CFGR_PLLMUL_SHIFT)
#define RCC_CFGR_USBPRE       (1 << 22)

#define RCC_CFGR_MCO_SHIFT    24
#define RCC_CFGR_MCO_MASK     (7 << RCC_CFGR_MCO_SHIFT)
#define RCC_CFGR_MCO_NONE     (0 << RCC_CFGR_MCO_SHIFT)
#define RCC_CFGR_MCO_SYSCLK   (4 << RCC_CFGR_MCO_SHIFT)
#define RCC_CFGR_MCO_HSI      (5 << RCC_CFGR_MCO_SHIFT)
#define RCC_CFGR_MCO_HSE      (6 << RCC_CFGR_MCO_SHIFT)
#define RCC_CFGR_MCO_PLLDIV2  (7 << RCC_CFGR_MCO_SHIFT)

/* RCC_CIR bits */

#define RCC_CIR_LSIRDYF  (1 <<  0)
#define RCC_CIR_LSERDYF  (1 <<  1)
#define RCC_CIR_HSIRDYF  (1 <<  2)
#define RCC_CIR_HSERDYF  (1 <<  3)
#define RCC_CIR_PLLRDYF  (1 <<  4)
#define RCC_CIR_CSSF     (1 <<  7)
#define RCC_CIR_LSIRDYE  (1 <<  8)
#define RCC_CIR_LSERDYE  (1 <<  9)
#define RCC_CIR_HSIRDYE  (1 << 10)
#define RCC_CIR_HSERDYE  (1 << 11)
#define RCC_CIR_PLLRDYE  (1 << 12)
#define RCC_CIR_LSIRDYC  (1 << 16)
#define RCC_CIR_LSERDYC  (1 << 17)
#define RCC_CIR_HSIRDYC  (1 << 18)
#define RCC_CIR_HSERDYC  (1 << 19)
#define RCC_CIR_PLLRDYC  (1 << 20)
#define RCC_CIR_CSSC     (1 << 23)

/* RCC_APB2RSTR */

#define RCC_APB2RSTR_AFIORST   (1 <<  0)
#define RCC_APB2RSTR_IOPARST   (1 <<  2)
#define RCC_APB2RSTR_IOPBRST   (1 <<  3)
#define RCC_APB2RSTR_IOPCRST   (1 <<  4)
#define RCC_APB2RSTR_IOPDRST   (1 <<  5)
#define RCC_APB2RSTR_IOPERST   (1 <<  6)
#define RCC_APB2RSTR_IOPFRST   (1 <<  7)
#define RCC_APB2RSTR_IOPGRST   (1 <<  8)
#define RCC_APB2RSTR_ADC1RST   (1 <<  9)
#define RCC_APB2RSTR_ADC2RST   (1 << 10)
#define RCC_APB2RSTR_TIM1RST   (1 << 11)
#define RCC_APB2RSTR_SPI1RST   (1 << 12)
#define RCC_APB2RSTR_TIM8RST   (1 << 13)
#define RCC_APB2RSTR_USART1RST (1 << 14)
#define RCC_APB2RSTR_ADC3RST   (1 << 15)
#define RCC_APB2RSTR_TIM9RST   (1 << 19)
#define RCC_APB2RSTR_TIM10RST  (1 << 20)
#define RCC_APB2RSTR_TIM11RST  (1 << 21)

/* RCC_APB1RSTR */

#define RCC_APB1RSTR_TIM2RST   (1 <<  0)
#define RCC_APB1RSTR_TIM3RST   (1 <<  1)
#define RCC_APB1RSTR_TIM4RST   (1 <<  2)
#define RCC_APB1RSTR_TIM5RST   (1 <<  3)
#define RCC_APB1RSTR_TIM6RST   (1 <<  4)
#define RCC_APB1RSTR_TIM7RST   (1 <<  5)
#define RCC_APB1RSTR_TIM12RST  (1 <<  6)
#define RCC_APB1RSTR_TIM13RST  (1 <<  7)
#define RCC_APB1RSTR_TIM14RST  (1 <<  8)
#define RCC_APB1RSTR_WWDGRST   (1 << 11)
#define RCC_APB1RSTR_SPI2RST   (1 << 14)
#define RCC_APB1RSTR_SPI3RST   (1 << 15)
#define RCC_APB1RSTR_USART2RST (1 << 17)
#define RCC_APB1RSTR_USART3RST (1 << 18)
#define RCC_APB1RSTR_UART4RST  (1 << 19)
#define RCC_APB1RSTR_UART5RST  (1 << 20)
#define RCC_APB1RSTR_I2C1RST   (1 << 21)
#define RCC_APB1RSTR_I2C2RST   (1 << 22)
#define RCC_APB1RSTR_USBRST    (1 << 23)
#define RCC_APB1RSTR_CANRST    (1 << 25)
#define RCC_APB1RSTR_BKPRST    (1 << 27)
#define RCC_APB1RSTR_PWRRST    (1 << 28)
#define RCC_APB1RSTR_DACRST    (1 << 29)

/* RCC_AHBENR */

#define RCC_AHBENR_DMA1EN     (1 <<  0)
#define RCC_AHBENR_DMA2EN     (1 <<  1)
#define RCC_AHBENR_SRAMEN     (1 <<  2) /* Applies in sleep mode */
#define RCC_AHBENR_FLITFEN    (1 <<  4) /* Applies in sleep mode */
#define RCC_AHBENR_CRCEN      (1 <<  6)
#define RCC_AHBENR_FSMCEN     (1 <<  8)
#define RCC_AHBENR_SDIOEN     (1 << 10)

/* RCC_APB2ENR */

#define RCC_APB2ENR_AFIOEN   (1 <<  0)
#define RCC_APB2ENR_IOPAEN   (1 <<  2)
#define RCC_APB2ENR_IOPBEN   (1 <<  3)
#define RCC_APB2ENR_IOPCEN   (1 <<  4)
#define RCC_APB2ENR_IOPDEN   (1 <<  5)
#define RCC_APB2ENR_IOPEEN   (1 <<  6)
#define RCC_APB2ENR_IOPFEN   (1 <<  7)
#define RCC_APB2ENR_IOPGEN   (1 <<  8)
#define RCC_APB2ENR_ADC1EN   (1 <<  9)
#define RCC_APB2ENR_ADC2EN   (1 << 10)
#define RCC_APB2ENR_TIM1EN   (1 << 11)
#define RCC_APB2ENR_SPI1EN   (1 << 12)
#define RCC_APB2ENR_TIM8EN   (1 << 13)
#define RCC_APB2ENR_USART1EN (1 << 14)
#define RCC_APB2ENR_ADC3EN   (1 << 15)
#define RCC_APB2ENR_TIM9EN   (1 << 19)
#define RCC_APB2ENR_TIM10EN  (1 << 20)
#define RCC_APB2ENR_TIM11EN  (1 << 21)

/* RCC_APB1ENR */

#define RCC_APB1ENR_TIM2EN   (1 <<  0)
#define RCC_APB1ENR_TIM3EN   (1 <<  1)
#define RCC_APB1ENR_TIM4EN   (1 <<  2)
#define RCC_APB1ENR_TIM5EN   (1 <<  3)
#define RCC_APB1ENR_TIM6EN   (1 <<  4)
#define RCC_APB1ENR_TIM7EN   (1 <<  5)
#define RCC_APB1ENR_TIM12EN  (1 <<  6)
#define RCC_APB1ENR_TIM13EN  (1 <<  7)
#define RCC_APB1ENR_TIM14EN  (1 <<  8)
#define RCC_APB1ENR_WWDGEN   (1 << 11)
#define RCC_APB1ENR_SPI2EN   (1 << 14)
#define RCC_APB1ENR_SPI3EN   (1 << 15)
#define RCC_APB1ENR_USART2EN (1 << 17)
#define RCC_APB1ENR_USART3EN (1 << 18)
#define RCC_APB1ENR_UART4EN  (1 << 19)
#define RCC_APB1ENR_UART5EN  (1 << 20)
#define RCC_APB1ENR_I2C1EN   (1 << 21)
#define RCC_APB1ENR_I2C2EN   (1 << 22)
#define RCC_APB1ENR_CAN1EN   (1 << 25)
#define RCC_APB1ENR_CAN2EN   (1 << 26)
#define RCC_APB1ENR_BKPEN    (1 << 27)
#define RCC_APB1ENR_PWREN    (1 << 28)
#define RCC_APB1ENR_DACEN    (1 << 29)

/* RCC_BDCR bits */

#define RCC_BDCR_LSEON         (1 <<  0)
#define RCC_BDCR_LSERDY        (1 <<  1)
#define RCC_BDCR_LSEBYP        (1 <<  2)
#define RCC_BDCR_RTCSEL_SHIFT  8
#define RCC_BDCR_RTCSEL_MASK   (3 << RCC_BDCR_RTCSEL_SHIFT)
#define RCC_BDCR_RTCSEL_NONE   (0 << RCC_BDCR_RTCSEL_SHIFT)
#define RCC_BDCR_RTCSEL_LSE    (1 << RCC_BDCR_RTCSEL_SHIFT)
#define RCC_BDCR_RTCSEL_LSI    (2 << RCC_BDCR_RTCSEL_SHIFT)
#define RCC_BDCR_RTCSEL_HSE128 (3 << RCC_BDCR_RTCSEL_SHIFT)
#define RCC_BDCR_RTCEN         (1 << 15)
#define RCC_BDCR_BDRST         (1 << 16)

/* RCC_CSR bits */

#define RCC_CSR_LSION    (1 <<  0)
#define RCC_CSR_LSIRDY   (1 <<  1)
#define RCC_CSR_RMVF     (1 << 24)
#define RCC_CSR_PINRSTF  (1 << 26)
#define RCC_CSR_PORRSTF  (1 << 27)
#define RCC_CSR_SFTRSTF  (1 << 28)
#define RCC_CSR_IWDGRSTF (1 << 29)
#define RCC_CSR_WWDGRSTF (1 << 30)
#define RCC_CSR_LPWRRSTF (1 << 31)

#endif /* __ARCH__ARMV6M__STM32F1__BITS__STM32F1OTHERS__RCC__H__ */

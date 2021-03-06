#ifndef _ARCH_ARMV7M_STM32L4_BITS_STM32L4X3XX_RCC_H_
#define _ARCH_ARMV7M_STM32L4_BITS_STM32L4X3XX_RCC_H_

#define STM32L4_RCC_CR          0x000
#define STM32L4_RCC_ICSCR       0x004
#define STM32L4_RCC_CFGR        0x008
#define STM32L4_RCC_PLLCFGR     0x00C
#define STM32L4_RCC_PLLSAI1CFGR 0x010
#define STM32L4_RCC_CIER        0x018
#define STM32L4_RCC_CIFR        0x01C
#define STM32L4_RCC_CICR        0x020
#define STM32L4_RCC_AHB1RSTR    0x028
#define STM32L4_RCC_AHB2RTSR    0x02C
#define STM32L4_RCC_AHB3RSTR    0x030
#define STM32L4_RCC_APB1RSTR1   0x038
#define STM32L4_RCC_APB1RSTR2   0x03C
#define STM32L4_RCC_APB2RSTR    0x040
#define STM32L4_RCC_AHB1ENR     0x048
#define STM32L4_RCC_AHB2ENR     0x04C
#define STM32L4_RCC_AHB3ENR     0x050
#define STM32L4_RCC_APB1ENR1    0x058
#define STM32L4_RCC_APB1ENR2    0x05C
#define STM32L4_RCC_APB2ENR     0x060
#define STM32L4_RCC_AHB1SMENR   0x068
#define STM32L4_RCC_AHB2SMENR   0x06C
#define STM32L4_RCC_AHB3SMENR   0x070
#define STM32L4_RCC_APB1SMENR1  0x078
#define STM32L4_RCC_APB1SMENR2  0x07C
#define STM32L4_RCC_APB2SMENR   0x080
#define STM32L4_RCC_CCIPR       0x088
#define STM32L4_RCC_BDCR        0x090
#define STM32L4_RCC_CSR         0x094
#define STM32L4_RCC_CRRCR       0x098
#define STM32L4_RCC_CCIPR2      0x09C

/* Register CR */
#define RCC_CR_MSION               (1<< 0)
#define RCC_CR_MSIRDY              (1<< 1)
#define RCC_CR_MSIPLLEN            (1<< 2)
#define RCC_CR_MSIREGSEL           (1<< 3)
#define RCC_CR_MSIRANGE_SHIFT      4
#define RCC_CR_MSIRANGE_MASK       (15<<RCC_CR_MSIRANGE_SHIFT)
#define RCC_CR_HSION               (1<< 8)
#define RCC_CR_HSIKERON            (1<< 9)
#define RCC_CR_HSIRDY              (1<<10)
#define RCC_CR_HSIASFS             (1<<11)
#define RCC_CR_HSEON               (1<<16)
#define RCC_CR_HSERDY              (1<<17)
#define RCC_CR_HSEBYP              (1<<18)
#define RCC_CR_CSSON               (1<<19)
#define RCC_CR_PLLON               (1<<24)
#define RCC_CR_PLLRDY              (1<<25)
#define RCC_CR_PLLSAI1ON           (1<<26)
#define RCC_CR_PLLSAI1RDY          (1<<27)

/* Register ICSR */
#define RCC_ICSR_MSICAL_SHIFT      0
#define RCC_ICSR_MSICAL_MASK       (0xFF<<RCC_ICSR_MSICAL_SHIFT)
#define RCC_ICSR_MSITRIM_SHIFT     8
#define RCC_ICSR_MSITRIM_MASK      (0xFF<<RCC_ICSR_MSITRIM_SHIFT)
#define RCC_ICSR_HSICAL_SHIFT      16
#define RCC_ICSR_HSICAL_MASK       (0xFF<<RCC_ICSR_HSICAL_SHIFT)
#define RCC_ICSR_HSITRIM_SHIFT     24
#define RCC_ICSR_HSITRIM_MASK      (0x1F<<RCC_ICSR_HSITRIM_SHIFT)

/* Register CFGR */
#define RCC_CFGR_SW_SHIFT          0
#define RCC_CFGR_SW_MASK           (3<<RCC_CFGR_SW_SHIFT)
#define RCC_CFGR_SWS_SHIFT         2
#define RCC_CFGR_SWS_MASK          (3<<RCC_CFGR_SWS_SHIFT)
#define RCC_CFGR_HPRE_SHIFT        4
#define RCC_CFGR_HPRE_MASK         (15<<RCC_CFGR_HPRE_SHIFT)
#define RCC_CFGR_PPRE1_SHIFT       8
#define RCC_CFGR_PPRE1_MASK        (3<<RCC_CFGR_PPRE1_SHIFT)
#define RCC_CFGR_PPRE2_SHIFT       11
#define RCC_CFGR_PPRE2_MASK        (3<<RCC_CFGR_PPRE2_SHIFT)
#define RCC_CFGR_STOPWUCK          (1<<15)
#define RCC_CFGR_MCOSEL_SHIFT      24
#define RCC_CFGR_MCOSEL_MASK       (7<<RCC_CFGR_MCOSEL_SHIFT)
#define RCC_CFGR_MCOPRE_SHIFT      28
#define RCC_CFGR_MCOPRE_MASK       (7<<RCC_CFGR_MCOPRE_SHIFT)

/* Register PLLCFGR */
#define RCC_PLLCFGR_PLLSRC_SHIFT   0
#define RCC_PLLCFGR_PLLSRC_MASK    (3<<RCC_PLLCFGR_PLLSRC_SHIFT)
#define RCC_PLLCFGR_PLLM_SHIFT     4
#define RCC_PLLCFGR_PLLM_MASK      (7<<RCC_PLLCFGR_PLLM_SHIFT)
#define RCC_PLLCFGR_PLLN_SHIFT     8
#define RCC_PLLCFGR_PLLN_MASK      (0x7F<<RCC_PLLCFGR_PLLN_SHIFT)
#define RCC_PLLCFGR_PLLPEN         (1<<16)
#define RCC_PLLCFGR_PLLP           (1<<17)
#define RCC_PLLCFGR_PLLQEN         (1<<20)
#define RCC_PLLCFGR_PLLQ_SHIFT     21
#define RCC_PLLCFGR_PLLQ_MASK      (3<<RCC_PLLCFGR_PLLQ_SHIFT)
#define RCC_PLLCFGR_PLLREN         (1<<24)
#define RCC_PLLCFGR_PLLR_SHIFT     25
#define RCC_PLLCFGR_PLLR_MASK      (3<<RCC_PLLCFGR_PLLR_SHIFT)

/* Register PLLSAI1CFGR */
#define RCC_PLLSAI1CFGR_PLLN_SHIFT 8
#define RCC_PLLSAI1CFGR_PLLN_MASK  (0x7F<<RCC_PLLSAI1CFGR_PLLN_SHIFT)
#define RCC_PLLSAI1CFGR_PLLPEN     (1<<16)
#define RCC_PLLSAI1CFGR_PLLP       (1<<17)
#define RCC_PLLSAI1CFGR_PLLQEN     (1<<20)
#define RCC_PLLSAI1CFGR_PLLQ_SHIFT 21
#define RCC_PLLSAI1CFGR_PLLQ_MASK  (3<<RCC_PLLSAI1CFGR_PLLQ_SHIFT)
#define RCC_PLLSAI1CFGR_PLLREN     (1<<24)
#define RCC_PLLSAI1CFGR_PLLR_SHIFT 25
#define RCC_PLLSAI1CFGR_PLLR_MASK  (3<<RCC_PLLSAI1CFGR_PLLR_SHIFT)

/* Register CIER TODO */
/* Register CIFR TODO */
/* Register CICR TODO */


/* Register AHB1RSTR */
#define RCC_AHB1RSTR_DMA1RST       (1<< 0)
#define RCC_AHB1RSTR_DMA2RST       (1<< 1)
#define RCC_AHB1RSTR_FLASHRST      (1<< 8)
#define RCC_AHB1RSTR_CRCRST        (1<<12)
#define RCC_AHB1RSTR_TSCRST        (1<<16)

/* Register AHB2RSTR */
#define RCC_AHB2RSTR_GPIOARST      (1<< 0)
#define RCC_AHB2RSTR_GPIOBRST      (1<< 1)
#define RCC_AHB2RSTR_GPIOCRST      (1<< 2)
#define RCC_AHB2RSTR_GPIODRST      (1<< 3)
#define RCC_AHB2RSTR_GPIOERST      (1<< 4)
#define RCC_AHB2RSTR_GPIOHRST      (1<< 7)
#define RCC_AHB2RSTR_ADCRST        (1<<13)
#define RCC_AHB2RSTR_AESRST        (1<<16)
#define RCC_AHB2RSTR_RNGRST        (1<<18)

/* Register AHB3RSTR */
#define RCC_AHB3RSTR_QSPIRST       (1<<8)

/* Register APB1RSTR1 */
#define RCC_APB1RSTR1_TIM2RST      (1<< 0)
#define RCC_APB1RSTR1_TIM3RST      (1<< 1)
#define RCC_APB1RSTR1_TIM6RST      (1<< 4)
#define RCC_APB1RSTR1_TIM7RST      (1<< 5)
#define RCC_APB1RSTR1_LCDRST       (1<< 9)
#define RCC_APB1RSTR1_SPI2RST      (1<<14)
#define RCC_APB1RSTR1_SPI3RST      (1<<15)
#define RCC_APB1RSTR1_USART2RST    (1<<17)
#define RCC_APB1RSTR1_USART3RST    (1<<18)
#define RCC_APB1RSTR1_UART4RST     (1<<19)
#define RCC_APB1RSTR1_I2C1RST      (1<<21)
#define RCC_APB1RSTR1_I2C2RST      (1<<22)
#define RCC_APB1RSTR1_I2C3RST      (1<<23)
#define RCC_APB1RSTR1_CRSRST       (1<<24)
#define RCC_APB1RSTR1_CAN1RST      (1<<25)
#define RCC_APB1RSTR1_USBFSRST     (1<<26)
#define RCC_APB1RSTR1_PWRRST       (1<<28)
#define RCC_APB1RSTR1_DAC1RST      (1<<29)
#define RCC_APB1RSTR1_OPAMPRST     (1<<30)
#define RCC_APB1RSTR1_LPTIM1RST    (1<<31)

/* Register APB1RSTR2 */
#define RCC_APB1RSTR2_LPUART1RST   (1<< 0)
#define RCC_APB1RSTR1_I2C4RST      (1<< 1)
#define RCC_APB1RSTR2_SWPMI1RST    (1<< 2)
#define RCC_APB1RSTR2_LPTIM2RST    (1<< 5)

/* Register APB2RSTR */
#define RCC_APB2RSTR_SYSCFGRST     (1<< 0)
#define RCC_APB2RSTR_SDMMC1RST     (1<<10)
#define RCC_APB2RSTR_TIM1RST       (1<<11)
#define RCC_APB2RSTR_SPI1RST       (1<<12)
#define RCC_APB2RSTR_USART1RST     (1<<14)
#define RCC_APB2RSTR_TIM15RST      (1<<16)
#define RCC_APB2RSTR_TIM16RST      (1<<17)
#define RCC_APB2RSTR_SAI1RST       (1<<21)
#define RCC_APB2RSTR_DFSDM1RST     (1<<24)

/* Register AHB1ENR */
#define RCC_AHB1ENR_DMA1EN         (1<< 0)
#define RCC_AHB1ENR_DMA2EN         (1<< 1)
#define RCC_AHB1ENR_FLASHEN        (1<< 8)
#define RCC_AHB1ENR_CRCEN          (1<<12)
#define RCC_AHB1ENR_TSCEN          (1<<16)

/* Register AHB2ENR */
#define RCC_AHB2ENR_GPIOAEN        (1<< 0)
#define RCC_AHB2ENR_GPIOBEN        (1<< 1)
#define RCC_AHB2ENR_GPIOCEN        (1<< 2)
#define RCC_AHB2ENR_GPIODEN        (1<< 3)
#define RCC_AHB2ENR_GPIOEEN        (1<< 4)
#define RCC_AHB2ENR_GPIOHEN        (1<< 7)
#define RCC_AHB2ENR_ADCEN          (1<<13)
#define RCC_AHB2ENR_AESEN          (1<<16)
#define RCC_AHB2ENR_RNGEN          (1<<18)

/* Register AHB3ENR */
#define RCC_AHB3ENR_QSPIEN         (1<<8)

/* Register APB1ENR1 */
#define RCC_APB1ENR1_TIM2EN        (1<< 0)
#define RCC_APB1ENR1_TIM3EN        (1<< 1)
#define RCC_APB1ENR1_TIM6EN        (1<< 4)
#define RCC_APB1ENR1_TIM7EN        (1<< 5)
#define RCC_APB1ENR1_LCDEN         (1<< 9)
#define RCC_APB1ENR1_RTCAPBEN      (1<<10)
#define RCC_APB1ENR1_WWDGEN        (1<<11)
#define RCC_APB1ENR1_SPI2EN        (1<<14)
#define RCC_APB1ENR1_SPI3EN        (1<<15)
#define RCC_APB1ENR1_USART2EN      (1<<17)
#define RCC_APB1ENR1_USART3EN      (1<<18)
#define RCC_APB1ENR1_UART4EN       (1<<19)
#define RCC_APB1ENR1_I2C1EN        (1<<21)
#define RCC_APB1ENR1_I2C2EN        (1<<22)
#define RCC_APB1ENR1_I2C3EN        (1<<23)
#define RCC_APB1ENR1_CRSEN         (1<<24)
#define RCC_APB1ENR1_CAN1EN        (1<<25)
#define RCC_APB1ENR1_USBFSEN       (1<<25)
#define RCC_APB1ENR1_PWREN         (1<<28)
#define RCC_APB1ENR1_DAC1EN        (1<<29)
#define RCC_APB1ENR1_OPAMPEN       (1<<30)
#define RCC_APB1ENR1_LPTIM1EN      (1<<31)

/* Register APB1ENR2 */
#define RCC_APB1ENR2_LPUART1EN     (1<< 0)
#define RCC_APB1ENR1_I2C4EN        (1<< 1)
#define RCC_APB1ENR2_SWPMI1EN      (1<< 2)
#define RCC_APB1ENR2_LPTIM2EN      (1<< 5)

/* Register APB2ENR */
#define RCC_APB2ENR_SYSCFGEN       (1<< 0)
#define RCC_APB2ENR_FWEN           (1<< 7)
#define RCC_APB2ENR_SDMMC1EN       (1<<10)
#define RCC_APB2ENR_TIM1EN         (1<<11)
#define RCC_APB2ENR_SPI1EN         (1<<12)
#define RCC_APB2ENR_USART1EN       (1<<14)
#define RCC_APB2ENR_TIM15EN        (1<<16)
#define RCC_APB2ENR_TIM16EN        (1<<17)
#define RCC_APB2ENR_SAI1EN         (1<<21)
#define RCC_APB2ENR_DFSDM1EN       (1<<24)

/* Register AHB1SMENR */
#define RCC_AHB1SMENR_DMA1SMEN     (1<< 0)
#define RCC_AHB1SMENR_DMA2SMEN     (1<< 1)
#define RCC_AHB1SMENR_FLASHSMEN    (1<< 8)
#define RCC_AHB1SMENR_SRAM1SMEN    (1<< 9)
#define RCC_AHB1SMENR_CRCSMEN      (1<<12)
#define RCC_AHB1SMENR_TSCSMEN      (1<<16)

/* Register AHB2SMENR */
#define RCC_AHB2SMENR_GPIOASMEN    (1<< 0)
#define RCC_AHB2SMENR_GPIOBSMEN    (1<< 1)
#define RCC_AHB2SMENR_GPIOCSMEN    (1<< 2)
#define RCC_AHB2SMENR_GPIODSMEN    (1<< 3)
#define RCC_AHB2SMENR_GPIOESMEN    (1<< 4)
#define RCC_AHB2SMENR_GPIOHSMEN    (1<< 7)
#define RCC_AHB2SMENR_SRAM2SMEN    (1<< 9)
#define RCC_AHB2SMENR_ADCSMEN      (1<<13)
#define RCC_AHB2SMENR_AESSMEN      (1<<16)
#define RCC_AHB2SEMNR_RNGSMEN      (1<<18)

/* Register AHB3SMENR */
#define RCC_AHB3SMENR_QSPISMEN     (1<< 8)

/* Register APB1SMENR1 */
#define RCC_APB1SMENR1_TIM2SMEN    (1<< 0)
#define RCC_APB1SMENR1_TIM3SMEN    (1<< 1)
#define RCC_APB1SMENR1_TIM6SMEN    (1<< 4)
#define RCC_APB1SMENR1_TIM7SMEN    (1<< 5)
#define RCC_APB1SMENR1_LCDSMEN     (1<< 9)
#define RCC_APB1SMENR1_RTCAPBSMEN  (1<<10)
#define RCC_APB1SMENR1_WWDGSMEN    (1<<11)
#define RCC_APB1SMENR1_SPI2SMEN    (1<<14)
#define RCC_APB1SMENR1_SPI3SMEN    (1<<15)
#define RCC_APB1SMENR1_USART2SMEN  (1<<17)
#define RCC_APB1SMENR1_USART3SMEN  (1<<18)
#define RCC_APB1SMENR1_UART4SMEN   (1<<19)
#define RCC_APB1SMENR1_I2C1SMEN    (1<<21)
#define RCC_APB1SMENR1_I2C2SMEN    (1<<22)
#define RCC_APB1SMENR1_I2C3SMEN    (1<<23)
#define RCC_APB1SMENR1_CRSSMEN     (1<<24)
#define RCC_APB1SMENR1_CAN1SMEN    (1<<25)
#define RCC_APB1SMENR1_PWRSMEN     (1<<28)
#define RCC_APB1SMENR1_DAC1SMEN    (1<<29)
#define RCC_APB1SMENR1_OPAMPSMEN   (1<<30)
#define RCC_APB1SMENR1_LPTIM1SMEN  (1<<31)

/* Register APB1SMENR2 */
#define RCC_APB1SMENR2_LPUART1SMEN (1<< 0)
#define RCC_APB1SMENR2_SWPMI1SMEN  (1<< 2)
#define RCC_APB1SMENR2_LPTIM2SMEN  (1<< 5)

/* Register APB2SMENR */
#define RCC_APB2SMENR_SYSCFGSMEN   (1<< 0)
#define RCC_APB2SMENR_SDMMC1SMEN   (1<<10)
#define RCC_APB2SMENR_TIM1SMEN     (1<<11)
#define RCC_APB2SMENR_SPI1SMEN     (1<<12)
#define RCC_APB2SMENR_USART1SMEN   (1<<14)
#define RCC_APB2SMENR_TIM15SMEN    (1<<16)
#define RCC_APB2SMENR_TIM16SMEN    (1<<17)
#define RCC_APB2SMENR_SAI1SMEN     (1<<21)

/* Register CCIPR TODO */

/* Register BDCR */
#define RCC_BDCR_LSEON             (1<<0)
#define RCC_BDCR_LSERDY            (1<<1)
#define RCC_BDCR_LSEBYP            (1<<2)
#define RCC_BDCR_LSEDRV_SHIFT      3
#define RCC_BDCR_LSEDRV_MASK       (3<<RCC_BDCR_LSEDRV_SHIFT)
#define RCC_BDCR_LSECSSON          (1<<5)
#define RCC_BDCR_LSECSSD           (1<<6)
#define RCC_BDCR_RTCSEL_SHIFT      8
#define RCC_BDCR_RTCSEL_MASK       (3<<RCC_BDCR_RTCSEL_SHIFT)
#define RCC_BDCR_RTCEN             (1<<15)
#define RCC_BDCR_BDRST             (1<<16)
#define RCC_BDCR_LSCOEN            (1<<24)
#define RCC_BDCR_LSCOSEL           (1<<25)

/* Register CSR */
#define RCC_CSR_LSION              (1<<0)
#define RCC_CSR_LSIRDY             (1<<1)
#define RCC_CSR_MSISRANGE_SHIFT    8
#define RCC_CSR_MSISRANGE_MASK     (15<<RCC_CSR_MSISRANGE_SHIFT)
#define RCC_CSR_RMVF               (1<<23)
#define RCC_CSR_FWRSTF             (1<<24)
#define RCC_CSR_OBLRSTF            (1<<25)
#define RCC_CSR_PINRSTF            (1<<26)
#define RCC_CSR_BORRSTF            (1<<27)
#define RCC_CSR_SFTRSTF            (1<<28)
#define RCC_CSR_IWDGRSTF           (1<<29)
#define RCC_CSR_WWDGRSTF           (1<<30)
#define RCC_CSR_LPWRRSTF           (1<<31)

/* Register CRRCR */
#define RCC_CRRCR_HSI48ON          0
#define RCC_CRRCR_HSI48RDY         1
#define RCC_CRRCR_HSI48CAL_SHIFT   7
#define RCC_CRRCR_HSI48CAL_MASK    (0x1FF<<RCC_CRRCR_HSI48CAL_SHIFT)

/* Register CCIPR2 TODO */

#endif

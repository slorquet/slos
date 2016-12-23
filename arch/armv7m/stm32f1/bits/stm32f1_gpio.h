#ifndef __ARCH__ARMV7M__STM32F1__BITS__STM32F1__GPIO__H__
#define __ARCH__ARMV7M__STM32F1__BITS__STM32F1__GPIO__H__

#define STM32F1_GPIO_CRL  0x00
#define STM32F1_GPIO_CRH  0x04
#define STM32F1_GPIO_IDR  0x08
#define STM32F1_GPIO_ODR  0x0C
#define STM32F1_GPIO_BSRR 0x10
#define STM32F1_GPIO_BRR  0x14
#define STM32F1_GPIO_LCKR 0x18

#define STM32F1_AFIO_EVCR    0x00
#define STM32F1_AFIO_MAPR    0x04
#define STM32F1_AFIO_EXTICR1 0x08
#define STM32F1_AFIO_EXTICR2 0x0C
#define STM32F1_AFIO_EXTICR3 0x10
#define STM32F1_AFIO_EXTICR4 0x14
#define STM32F1_AFIO_MAPR2   0x18

/* GPIO conf registers */

#define GPIO_MODE_MASK     0x03
#define GPIO_MODE_INPUT    0x00
#define GPIO_MODE_OUT10MHZ 0x01
#define GPIO_MODE_OUT2MHZ  0x02
#define GPIO_MODE_OUT50MHZ 0x03

#define GPIO_CNF_MASK    (0x03 << 2)
#define GPIO_CNF_ANALOG  (0x00 << 2)
#define GPIO_CNF_INFLOAT (0x01 << 2)
#define GPIO_CNF_INPULL  (0x02 << 2)

#define GPIO_CNF_ALT     0x02 /* 0x00 is GP */
#define GPIO_CNF_OD      0x01 /* 0x00 is PP */

/* MAPR bits */

#ifdef STM32F1_LINE_CONNECTIVITY

/* Definitions for Connectivity line */

#define AFIO_MAPR_SPI1_REMAP              (1<<0)
#define AFIO_MAPR_I2C1_REMAP              (1<<1)
#define AFIO_MAPR_USART1_REMAP            (1<<2)
#define AFIO_MAPR_USART2_REMAP            (1<<3)
#define AFIO_MAPR_USART3_REMAP_SHIFT      4
#define AFIO_MAPR_USART3_REMAP_MASK       (3<<AFIO_MAPR_USART3_REMAP_SHIFT)
#define AFIO_MAPR_TIM1_REMAP_SHIFT        6
#define AFIO_MAPR_TIM1_REMAP_MASK         (3<<AFIO_MAPR_TIM1_REMAP_SHIFT)
#define AFIO_MAPR_TIM2_REMAP_SHIFT        8
#define AFIO_MAPR_TIM2_REMAP_MASK         (3<<AFIO_MAPR_TIM2_REMAP_SHIFT)
#define AFIO_MAPR_TIM3_REMAP_SHIFT        10
#define AFIO_MAPR_TIM3_REMAP_MASK         (3<<AFIO_MAPR_TIM3_REMAP_SHIFT)
#define AFIO_MAPR_TIM4_REMAP              (1<<12)
#define AFIO_MAPR_CAN1_REMAP_SHIFT        13
#define AFIO_MAPR_CAN1_REMAP_MASK         (3<<AFIO_MAPR_CAN1_REMAP_SHIFT)
#define AFIO_MAPR_PD01_REMAP              (1<<15)
#define AFIO_MAPR_TIM5CH4_IREMAP          (1<<16)
#define AFIO_MAPR_ETH_REMAP               (1<<21)
#define AFIO_MAPR_CAN2_REMAP              (1<<22)
#define AFIO_MAPR_MII_RMII_SEL            (1<<23)
#define AFIO_MAPR_SWJ_CFG_SHIFT           24
#define AFIO_MAPR_SWJ_CFG_MASK            (7<<AFIO_MAPR_SWJ_CFG_SHIFT)
#define AFIO_MAPR_SWJ_CFG_FULL_SWJ        (0<<AFIO_MAPR_SWJ_CFG_SHIFT)
#define AFIO_MAPR_SWJ_CFG_FULL_SWJ_NO_RST (1<<AFIO_MAPR_SWJ_CFG_SHIFT)
#define AFIO_MAPR_SWJ_CFG_SW_DP           (2<<AFIO_MAPR_SWJ_CFG_SHIFT)
#define AFIO_MAPR_SWJ_CFG_JTAG_DP         (4<<AFIO_MAPR_SWJ_CFG_SHIFT)
#define AFIO_MAPR_SPI3_REMAP              (1<<28)
#define AFIO_MAPR_TIM2ITR1_IREMAP         (1<<29)
#define AFIO_MAPR_PTP_PPS_REMAP           (1<<30)

#else

/* Definitions for low, medium, high and XL density devices */

#define AFIO_MAPR_SPI1_REMAP              (1<<0)
#define AFIO_MAPR_I2C1_REMAP              (1<<1)
#define AFIO_MAPR_USART1_REMAP            (1<<2)
#define AFIO_MAPR_USART2_REMAP            (1<<3)
#define AFIO_MAPR_USART3_REMAP_SHIFT      4
#define AFIO_MAPR_USART3_REMAP_MASK       (3<<AFIO_MAPR_USART3_REMAP_SHIFT)
#define AFIO_MAPR_TIM1_REMAP_SHIFT        6
#define AFIO_MAPR_TIM1_REMAP_MASK         (3<<AFIO_MAPR_TIM1_REMAP_SHIFT)
#define AFIO_MAPR_TIM2_REMAP_SHIFT        8
#define AFIO_MAPR_TIM2_REMAP_MASK         (3<<AFIO_MAPR_TIM2_REMAP_SHIFT)
#define AFIO_MAPR_TIM3_REMAP_SHIFT        10
#define AFIO_MAPR_TIM3_REMAP_MASK         (3<<AFIO_MAPR_TIM3_REMAP_SHIFT)
#define AFIO_MAPR_TIM4_REMAP              (1<<12)
#define AFIO_MAPR_CAN1_REMAP_SHIFT        13
#define AFIO_MAPR_CAN1_REMAP_MASK         (3<<AFIO_MAPR_CAN1_REMAP_SHIFT)
#define AFIO_MAPR_PD01_REMAP              (1<<15)
#define AFIO_MAPR_TIM5CH4_IREMAP          (1<<16)
#define AFIO_MAPR_ADC1_ETRGINJ_REMAP      (1<<17)
#define AFIO_MAPR_ADC1_ETRGREG_REMAP      (1<<18)
#define AFIO_MAPR_ADC2_ETRGINJ_REMAP      (1<<19)
#define AFIO_MAPR_ADC2_ETRGREG_REMAP      (1<<20)
#define AFIO_MAPR_SWJ_CFG_SHIFT           24
#define AFIO_MAPR_SWJ_CFG_MASK            (7<<AFIO_MAPR_SWJ_CFG_SHIFT)
#define AFIO_MAPR_SWJ_CFG_FULL_SWJ        (0<<AFIO_MAPR_SWJ_CFG_SHIFT)
#define AFIO_MAPR_SWJ_CFG_FULL_SWJ_NO_RST (1<<AFIO_MAPR_SWJ_CFG_SHIFT)
#define AFIO_MAPR_SWJ_CFG_SW_DP           (2<<AFIO_MAPR_SWJ_CFG_SHIFT)
#define AFIO_MAPR_SWJ_CFG_JTAG_DP         (4<<AFIO_MAPR_SWJ_CFG_SHIFT)

#endif

/* MAPR2 bits */

#define AFIO_MAPR2_TIM9_REMAP             (1<<5)
#define AFIO_MAPR2_TIM10_REMAP            (1<<6)
#define AFIO_MAPR2_TIM11_REMAP            (1<<7)
#define AFIO_MAPR2_TIM13_REMAP            (1<<8)
#define AFIO_MAPR2_TIM14_REMAP            (1<<9)
#define AFIO_MAPR2_FSMC_NADV              (1<<10)

#endif

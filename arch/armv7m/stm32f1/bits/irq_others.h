#ifndef __ARCH__ARMV6M__STM32F1__BITS__IRQ__OTHERS__H__
#define __ARCH__ARMV6M__STM32F1__BITS__IRQ__OTHERS__H__

#include <assert.h>

enum IRQS
{
  STM32F1_IRQ_WWDG,
  STM32F1_IRQ_PVD,
  STM32F1_IRQ_TAMPER,
  STM32F1_IRQ_RTC,
  STM32F1_IRQ_FLASH,
  STM32F1_IRQ_RCC,
  STM32F1_IRQ_EXTI0,
  STM32F1_IRQ_EXTI1,
  STM32F1_IRQ_EXTI2,
  STM32F1_IRQ_EXTI3,
  STM32F1_IRQ_EXTI4,
  STM32F1_IRQ_DMA1_CH1,
  STM32F1_IRQ_DMA1_CH2,
  STM32F1_IRQ_DMA1_CH3,
  STM32F1_IRQ_DMA1_CH4,
  STM32F1_IRQ_DMA1_CH5,
  STM32F1_IRQ_DMA1_CH6,
  STM32F1_IRQ_DMA1_CH7,
  STM32F1_IRQ_ADC1_2,
  STM32F1_IRQ_USB_HP_CAN1_TX,
  STM32F1_IRQ_USB_LP_CAN1_RX0,
  STM32F1_IRQ_CAN1_RX1,
  STM32F1_IRQ_CAN1_SCE,
  STM32F1_IRQ_EXTI9_5,
  STM32F1_IRQ_TIM1_BRK,
  STM32F1_IRQ_TIM1_UP,
  STM32F1_IRQ_TIM1_TRG_COM,
  STM32F1_IRQ_TIM1_CC,
  STM32F1_IRQ_TIM2,
  STM32F1_IRQ_TIM3,
  STM32F1_IRQ_TIM4,
  STM32F1_IRQ_I2C1_EV,
  STM32F1_IRQ_I2C1_ER,
  STM32F1_IRQ_I2C2_EV,
  STM32F1_IRQ_I2C2_ER,
  STM32F1_IRQ_SPI1,
  STM32F1_IRQ_SPI2,
  STM32F1_IRQ_USART1,
  STM32F1_IRQ_USART2,
  STM32F1_IRQ_USART3,
  STM32F1_IRQ_EXTI15_10,
  STM32F1_IRQ_RTC_ALARM,
  STM32F1_IRQ_USB_WKUP,
  STM32F1_IRQ_TIM8_BRK,
  STM32F1_IRQ_TIM8_UP,
  STM32F1_IRQ_TIM8_TRG_COM,
  STM32F1_IRQ_TIM8_CC,
  STM32F1_IRQ_ADC3,
  STM32F1_IRQ_FSMC,
  STM32F1_IRQ_SDIO,
  STM32F1_IRQ_TIM5,
  STM32F1_IRQ_SPI3,
  STM32F1_IRQ_UART4,
  STM32F1_IRQ_UART5,
  STM32F1_IRQ_TIM6,
  STM32F1_IRQ_TIM7,
  STM32F1_IRQ_DMA2_CH1,
  STM32F1_IRQ_DMA2_CH2,
  STM32F1_IRQ_DMA2_CH3,
  STM32F1_IRQ_DMA2_CH4_5,
  
  ARCH_CHIP_NIRQS
};

static_assert(ARCH_CHIP_NIRQS==60);

#endif
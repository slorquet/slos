#ifndef STM32_CLOCK
#define STM32_CLOCK

#include <stdint.h>

#define STM32_REG_RCC_BASE	0x40023800
#define STM32_REG_RCC_AHB1ENR	(STM32_REG_RCC_BASE + 0x030)
#define STM32_REG_RCC_APB1ENR	(STM32_REG_RCC_BASE + 0x040)
#define STM32_REG_RCC_APB2ENR	(STM32_REG_RCC_BASE + 0x044)

void stm32_clock_default(void);
uint32_t stm32_clock_get(void);

#endif //STM32_CLOCK

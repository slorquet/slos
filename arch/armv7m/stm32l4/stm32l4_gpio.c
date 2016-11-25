#include <stdint.h>

#include "armv7m.h"
#include "stm32l4_rcc.h"
#include "bits/stm32l4_gpio.h"
#include "stm32l4_gpio.h"

struct gpio_params {
    uint32_t base;
    uint32_t ckenreg;
    uint32_t ckenbit;
};


static const struct gpio_params g_gpio[11] = {
#ifdef STM32L4_HAVE_GPIO_A
    [ 0] = {0x40020000, STM32L4_REG_RCC_AHB1ENR, 0},
#endif
#ifdef STM32L4_HAVE_GPIO_B
    [ 1] = {0x40020400, STM32L4_REG_RCC_AHB1ENR, 1},
#endif
#ifdef STM32L4_HAVE_GPIO_C
    [ 2] = {0x40020800, STM32L4_REG_RCC_AHB1ENR, 2},
#endif
#ifdef STM32L4_HAVE_GPIO_D
    [ 3] = {0x40020C00, STM32L4_REG_RCC_AHB1ENR, 3},
#endif
#ifdef STM32L4_HAVE_GPIO_E
    [ 4] = {0x40021000, STM32L4_REG_RCC_AHB1ENR, 4},
#endif
#ifdef STM32L4_HAVE_GPIO_F
    [ 5] = {0x40021400, STM32L4_REG_RCC_AHB1ENR, 5},
#endif
#ifdef STM32L4_HAVE_GPIO_G
    [ 6] = {0x40021800, STM32L4_REG_RCC_AHB1ENR, 6},
#endif
#ifdef STM32L4_HAVE_GPIO_H
    [ 7] = {0x40021C00, STM32L4_REG_RCC_AHB1ENR, 7},
#endif
#ifdef STM32L4_HAVE_GPIO_I
    [ 8] = {0x40022000, STM32L4_REG_RCC_AHB1ENR, 8},
#endif
#ifdef STM32L4_HAVE_GPIO_J
    [ 9] = {0x40022400, STM32L4_REG_RCC_AHB1ENR, XXX},
#endif
#ifdef STM32L4_HAVE_GPIO_K
    [10] = {0x40022800, STM32L4_REG_RCC_AHB1ENR, XXX},
#endif
};

void stm32l4_gpio_init(uint32_t gpiodesc)
{
	uint32_t line = (gpiodesc & STM32L4_GPIO_FLAGS_MASK_LINE) >> STM32L4_GPIO_FLAGS_SHIFT_LINE;
	uint32_t port = (gpiodesc & STM32L4_GPIO_FLAGS_MASK_PORT) >> STM32L4_GPIO_FLAGS_SHIFT_PORT;
	uint32_t base,reg,val;

	//get port base address
	if(port >= STM32L4_GPIO_PORT_COUNT) return;
	base = g_gpio[port].base;
	if(!base) return; //this port is not implemented

	//Enable clock to GPIO peripheral
	reg = g_gpio[port].ckenreg;
	val = getreg32(reg);
	val |= (1<<g_gpio[port].ckenbit);
	putreg32(reg, val);

	//configure 1-bit ports
	//Offset 04 OTYPER
	val = (gpiodesc & STM32L4_GPIO_FLAGS_MASK_TYPE) >> STM32L4_GPIO_FLAGS_SHIFT_TYPE;
	reg = getreg32(base + STM32L4_REGOFF_GPIO_OTYPER);
	reg &= ~(1<<line);
	reg |= (val<<line);
	putreg32(base + STM32L4_REGOFF_GPIO_OTYPER, reg);
	
	//configure 2-bit ports
	line += line;
	
	//Offset 00 MODER
	val = (gpiodesc & STM32L4_GPIO_FLAGS_MASK_MODE) >> STM32L4_GPIO_FLAGS_SHIFT_MODE;
	reg = getreg32(base + STM32L4_REGOFF_GPIO_MODER);
	reg &= ~(3<<line);
	reg |= (val<<line);
	putreg32(base + STM32L4_REGOFF_GPIO_MODER, reg);
	
	//Offset 08 OSPEEDER
	val = (gpiodesc & STM32L4_GPIO_FLAGS_MASK_SPD) >> STM32L4_GPIO_FLAGS_SHIFT_SPD;
	reg = getreg32(base + STM32L4_REGOFF_GPIO_OSPEEDER);
	reg &= ~(3<<line);
	reg |= (val<<line);
	putreg32(base + STM32L4_REGOFF_GPIO_OSPEEDER, reg);

	//Offset 0C PUPDR
	val = (gpiodesc & STM32L4_GPIO_FLAGS_MASK_PULL) >> STM32L4_GPIO_FLAGS_SHIFT_PULL;
	reg = getreg32(base + STM32L4_REGOFF_GPIO_PUPDR);
	reg &= ~(3<<line);
	reg |= (val<<line);
	putreg32(base + STM32L4_REGOFF_GPIO_PUPDR, reg);

	//configure 4-bit ports
	line += line;
	
	//Offset 20 AFRL (for lines 0-7)
	//Offset 24 AFRH (for lines 8-15)
	val = (gpiodesc & STM32L4_GPIO_FLAGS_MASK_ALT) >> STM32L4_GPIO_FLAGS_SHIFT_ALT;
	if(line<(8<<2)) {
		reg = getreg32(base + STM32L4_REGOFF_GPIO_AFRL);
		reg &= ~(15<<line);
		reg |= (val<<line);
		putreg32(base + STM32L4_REGOFF_GPIO_AFRL, reg);
	} else {
                line -= 32;
		reg = getreg32(base + STM32L4_REGOFF_GPIO_AFRH);
		reg &= ~(15<<line);
		reg |= (val<<line);
		putreg32(base + STM32L4_REGOFF_GPIO_AFRH, reg);
	}
}

void stm32l4_gpio_write(uint32_t gpio, int state)
{
	uint32_t line = (gpio & STM32L4_GPIO_FLAGS_MASK_LINE) >> STM32L4_GPIO_FLAGS_SHIFT_LINE;
	uint32_t port = (gpio & STM32L4_GPIO_FLAGS_MASK_PORT) >> STM32L4_GPIO_FLAGS_SHIFT_PORT;
	uint32_t base,reg,val;

	//get port base address
	if(port >= STM32L4_GPIO_PORT_COUNT) return;
	base = g_gpio[port].base;
	if(!base) return; //this port is not implemented

	if(!state) line += 16; //access BR instead of BS
	base += STM32L4_REGOFF_GPIO_BSRR;
	putreg32(base, 1<<line);
}

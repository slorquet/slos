#ifndef __ARCH__ARMV7M__STM32L4__STM32L4__SPI__H__
#define __ARCH__ARMV7M__STM32L4__STM32L4__SPI__H__

#include <stdint.h>
#include <slos/spimaster.h>

struct spi_master_s *stm32l4_spi_init(uint32_t spiid);

#endif /* __ARCH__ARMV7M__STM32L4__STM32L4__SPI__H__ */


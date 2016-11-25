#include <stdint.h>

#include "stm32l4_rcc.h"
#include "stm32l4_gpio.h"
#include "stm32l4_uart.h"
#include "stm32l4_spi.h"

/*for now, lock in case of exception*/

uint8_t tx[8], rx[22];

void puthb(uint32_t uartid, uint8_t b)
{
  static const char hex[]="0123456789ABCDEF";
  char ch[3];
  stm32l4_uart_send(uartid, hex[b>> 4]);
  stm32l4_uart_send(uartid, hex[b&0xf]);
}

void board_start(void)
{
	
    /*16 Mhz internal clock*/
    stm32l4_clock_default();

    /* setup standard GPIO pins for uart 2*/
    stm32l4_gpio_init(STM32L4_GPIO_PORT_A | STM32L4_GPIO_PIN_2 | STM32L4_GPIO_MODE_ALT | STM32L4_GPIO_ALT_7 | STM32L4_GPIO_PULL_UP | STM32L4_GPIO_TYPE_PP ); /*TX PIN ON A2*/
    stm32l4_gpio_init(STM32L4_GPIO_PORT_A | STM32L4_GPIO_PIN_3 | STM32L4_GPIO_MODE_ALT | STM32L4_GPIO_ALT_7 | STM32L4_GPIO_PULL_UP | STM32L4_GPIO_TYPE_PP ); /*RX PIN ON A3*/

    /*init uart 2*/
    stm32l4_uart_init(STM32L4_USART_2);
    stm32l4_uart_setbaud(STM32L4_USART_2, 115200);

    /*write something*/
    stm32l4_uart_write_string(STM32L4_USART_2,"Hello world\r\n");
	
    /*switch the LED on (it's on PA5)*/
    stm32l4_gpio_init(STM32L4_GPIO_PORT_A | STM32L4_GPIO_PIN_5 | STM32L4_GPIO_MODE_OUT | STM32L4_GPIO_PULL_UP | STM32L4_GPIO_TYPE_PP ); /*LED PIN ON A5*/
    stm32l4_gpio_write(STM32L4_GPIO_PORT_A | STM32L4_GPIO_PIN_5, 1);
	
#if STM32L4_CHIP == STM32F407V
#define GPIO_SPI_CS (STM32L4_GPIO_PORT_B | STM32L4_GPIO_PIN_12)
    /*configure SPI2 (AF5) on pins:
      PB12(ncs)
      PB13(sclk)
      PB14(miso)
      PB15(mosi)
*/
    stm32l4_gpio_init(GPIO_SPI_CS                             | STM32L4_GPIO_MODE_OUT |                    STM32L4_GPIO_PULL_UP   | STM32L4_GPIO_TYPE_PP ); /* NCS2 ON PB12, default high (pullup) */
    stm32l4_gpio_init(STM32L4_GPIO_PORT_B | STM32L4_GPIO_PIN_13   | STM32L4_GPIO_MODE_ALT | STM32L4_GPIO_ALT_5 | STM32L4_GPIO_PULL_DOWN | STM32L4_GPIO_TYPE_PP | STM32L4_GPIO_SPD_MED); /*SCLK2 ON PB13, default low (pulldn) */
    stm32l4_gpio_init(STM32L4_GPIO_PORT_B | STM32L4_GPIO_PIN_14   | STM32L4_GPIO_MODE_ALT | STM32L4_GPIO_ALT_5 | STM32L4_GPIO_PULL_UP   | STM32L4_GPIO_TYPE_PP | STM32L4_GPIO_SPD_MED); /*MISO2 ON PB14 */
    stm32l4_gpio_init(STM32L4_GPIO_PORT_B | STM32L4_GPIO_PIN_15   | STM32L4_GPIO_MODE_ALT | STM32L4_GPIO_ALT_5 | STM32L4_GPIO_PULL_UP   | STM32L4_GPIO_TYPE_PP | STM32L4_GPIO_SPD_MED); /*MOSI2 ON PB15*/
    /*initial value*/
    stm32l4_gpio_write(GPIO_SPI_CS, 1);
#endif

    /*Configure SPI2*/
    stm32l4_spi_init(STM32L4_SPI_2, STM32L4_SPI_MSBFIRST | STM32L4_SPI_MODE_0 | STM32L4_SPI_BAUDDIV_8);

    /*Read JEDEC ID from flash*/
    tx[0] = 0x9F;
    tx[1] = 0x00;
    tx[2] = 0x00;
    tx[3] = 0x00;
    while(1) {
      uint32_t i;
      stm32l4_gpio_write(GPIO_SPI_CS, 0);
      stm32l4_spi_transac8(STM32L4_SPI_2, 4, tx, rx);
      stm32l4_gpio_write(GPIO_SPI_CS, 1);
      stm32l4_uart_write_string(STM32L4_USART_2,"JEDEC ID: ");
      puthb(STM32L4_USART_2, rx[1]);
      puthb(STM32L4_USART_2, rx[2]);
      puthb(STM32L4_USART_2, rx[3]);
      stm32l4_uart_write_string(STM32L4_USART_2,"\r\n");
      for(i=0;i<1000;i++) asm("nop");
    }
    /* id is available*/
    /* 25P16 : 202013  */
    /* 25Q032: 20BA16  */
}

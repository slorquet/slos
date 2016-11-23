#include "config.h"

#include <stdint.h>

#include "stm32.h"
#include "stm32_clock.h"
#include "stm32_gpio.h"
#include "stm32_uart.h"
#include "stm32_spi.h"

/*for now, lock in case of exception*/
void _except(void) { while(1); }

uint8_t tx[8], rx[22];

void puthb(uint32_t uartid, uint8_t b)
{
  static const char hex[]="0123456789ABCDEF";
  char ch[3];
  stm32_uart_send(uartid, hex[b>> 4]);
  stm32_uart_send(uartid, hex[b&0xf]);
}

void main(void)
{
	
    /*16 Mhz internal clock*/
    stm32_clock_default();

    /* setup standard GPIO pins for uart 2*/
    stm32_gpio_init(STM32_GPIO_PORT_A | STM32_GPIO_PIN_2 | STM32_GPIO_MODE_ALT | STM32_GPIO_ALT_7 | STM32_GPIO_PULL_UP | STM32_GPIO_TYPE_PP ); /*TX PIN ON A2*/
    stm32_gpio_init(STM32_GPIO_PORT_A | STM32_GPIO_PIN_3 | STM32_GPIO_MODE_ALT | STM32_GPIO_ALT_7 | STM32_GPIO_PULL_UP | STM32_GPIO_TYPE_PP ); /*RX PIN ON A3*/

    /*init uart 2*/
    stm32_uart_init(STM32_USART_2);
    stm32_uart_setbaud(STM32_USART_2, 115200);

    /*write something*/
    stm32_uart_write_string(STM32_USART_2,"Hello world\r\n");
	
    /*switch the LED on (it's on PA5)*/
    stm32_gpio_init(STM32_GPIO_PORT_A | STM32_GPIO_PIN_5 | STM32_GPIO_MODE_OUT | STM32_GPIO_PULL_UP | STM32_GPIO_TYPE_PP ); /*LED PIN ON A5*/
    stm32_gpio_write(STM32_GPIO_PORT_A | STM32_GPIO_PIN_5, 1);
	
#if STM32_CHIP == STM32F407V
#define GPIO_SPI_CS (STM32_GPIO_PORT_B | STM32_GPIO_PIN_12)
    /*configure SPI2 (AF5) on pins:
      PB12(ncs)
      PB13(sclk)
      PB14(miso)
      PB15(mosi)
*/
    stm32_gpio_init(GPIO_SPI_CS                             | STM32_GPIO_MODE_OUT |                    STM32_GPIO_PULL_UP   | STM32_GPIO_TYPE_PP ); /* NCS2 ON PB12, default high (pullup) */
    stm32_gpio_init(STM32_GPIO_PORT_B | STM32_GPIO_PIN_13   | STM32_GPIO_MODE_ALT | STM32_GPIO_ALT_5 | STM32_GPIO_PULL_DOWN | STM32_GPIO_TYPE_PP | STM32_GPIO_SPD_MED); /*SCLK2 ON PB13, default low (pulldn) */
    stm32_gpio_init(STM32_GPIO_PORT_B | STM32_GPIO_PIN_14   | STM32_GPIO_MODE_ALT | STM32_GPIO_ALT_5 | STM32_GPIO_PULL_UP   | STM32_GPIO_TYPE_PP | STM32_GPIO_SPD_MED); /*MISO2 ON PB14 */
    stm32_gpio_init(STM32_GPIO_PORT_B | STM32_GPIO_PIN_15   | STM32_GPIO_MODE_ALT | STM32_GPIO_ALT_5 | STM32_GPIO_PULL_UP   | STM32_GPIO_TYPE_PP | STM32_GPIO_SPD_MED); /*MOSI2 ON PB15*/
    /*initial value*/
    stm32_gpio_write(GPIO_SPI_CS, 1);
#endif

    /*Configure SPI2*/
    stm32_spi_init(STM32_SPI_2, STM32_SPI_MSBFIRST | STM32_SPI_MODE_0 | STM32_SPI_BAUDDIV_8);

    /*Read JEDEC ID from flash*/
    tx[0] = 0x9F;
    tx[1] = 0x00;
    tx[2] = 0x00;
    tx[3] = 0x00;
    while(1) {
      uint32_t i;
      stm32_gpio_write(GPIO_SPI_CS, 0);
      stm32_spi_transac8(STM32_SPI_2, 4, tx, rx);
      stm32_gpio_write(GPIO_SPI_CS, 1);
      stm32_uart_write_string(STM32_USART_2,"JEDEC ID: ");
      puthb(STM32_USART_2, rx[1]);
      puthb(STM32_USART_2, rx[2]);
      puthb(STM32_USART_2, rx[3]);
      stm32_uart_write_string(STM32_USART_2,"\r\n");
      for(i=0;i<1000;i++) asm("nop");
    }
    /* id is available*/
    /* 25P16 : 202013  */
    /* 25Q032: 20BA16  */
}

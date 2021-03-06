#ifndef _ARCH_ARMV7M_STM32L4_STM32L4_UART_H_
#define _ARCH_ARMV7M_STM32L4_STM32L4_UART_H_

#include <stdint.h>

//indices for API
enum {
    STM32F4_USART_1,
    STM32F4_USART_2,
    STM32F4_USART_3,
    STM32F4_USART_4,
    STM32F4_USART_5,
    STM32F4_USART_6,
    STM32F4_USART_7,
    STM32F4_USART_8
};

void stm32f4_uart_init(uint32_t uartid);
void stm32f4_uart_setbaud(uint32_t uartid, uint32_t baud);
void stm32f4_uart_send(uint32_t uartid, int data);
void stm32f4_uart_write_string(uint32_t uartid, const char *s);

#endif /* _ARCH_ARMV7M_STM32L4_STM32L4_UART_H_ */

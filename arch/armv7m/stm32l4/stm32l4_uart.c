#include <stdint.h>

#include "armv7m.h"
#include "bits/stm32l4_rcc.h"
#include "bits/stm32l4_uart.h"
#include "stm32l4_rcc.h"
#include "stm32l4_uart.h"

struct uart_params {
	uint32_t base;
	uint32_t ckenreg;
	uint32_t ckenbit;
};

static const struct uart_params g_uart[] = {
#ifdef STM32_HAVE_USART_1
    [0] = {STM32L4_REGBASE_USART1, STM32L4_REGOFF_RCC_APB2ENR, 4},
#endif
#ifdef STM32_HAVE_USART_2
    [1] = {STM32L4_REGBASE_USART2, STM32L4_REGOFF_RCC_APB1ENR, 17},
#endif
#ifdef STM32_HAVE_USART_3
    [2] = {0x40004800, STM32L4_REGOFF_RCC_APB1ENR, 18},
#endif
#ifdef STM32_HAVE_UART_4
    [3] = {0x40004C00, STM32L4_REGOFF_RCC_APB1ENR, 19},
#endif
#ifdef STM32_HAVE_UART_5
    [4] = {0x40005000, STM32L4_REGOFF_RCC_APB1ENR, 20},
#endif
#ifdef STM32_HAVE_USART_6
    [5] = {0x40011400, STM32L4_REGOFF_RCC_APB2ENR, 5},
#endif
#ifdef STM32_HAVE_UART_7
    [6] = {0x40007800, XXX,XXX}
#endif
#ifdef STM32_HAVE_UART_8
    [7] = {0x40007C00, XXX,XXX}
#endif
};

void stm32l4_uart_init(uint32_t uartid)
{
    uint32_t base;
    uint32_t reg;
    uint32_t val;

    if(uartid>8) return;
    base = g_uart[uartid].base;
    if(base==0) return;

    //Enable clock to UART peripheral
    reg = g_uart[uartid].ckenreg;
    val = getreg32(reg);
    val |= (1<<g_uart[uartid].ckenbit);
    putreg32(reg, val);

    //configure registers for a simple uart, 8 bits, 1 stop bit, no parity
    //CR1: OVER8=0, UE=1, M=0, WAKE=0, PCE=0, no parity, no interrupts, RE=1, RWU=0
    reg = base + STM32_REGOFF_USART_CR1;
    val = STM32_REGMASK_USART_CR1_UE | STM32_REGMASK_USART_CR1_RE | STM32_REGMASK_USART_CR1_TE;
    putreg32(reg, getreg32(reg) & 0x0000BFFF | val);
    //CR2: LINEN=0, STOP=00, CLKEN=0, no cpol, no cpha, no lbcl, no lin
    reg = base + STM32_REGOFF_USART_CR2;
    putreg32(reg, getreg32(reg) & 0x00007F6F);
    //CR3: ONEBIT=0, no interrupts, CTSE=0, RTSE=0, no dma, SCEN=0, NACK=0, HDSEL=0, no irda
    reg = base + STM32_REGOFF_USART_CR3;
    putreg32(reg, getreg32(reg) & 0x00000FFF);

}

/*
 * Fclk      baud      float     int(16times) hex   int part   frac part      approximated
 * 16 MHz    115200    8,68055   138          0x8A  8          10/16 = 0.625  8.625
 */
void stm32l4_uart_setbaud(uint32_t uartid, uint32_t baud)
{
    uint32_t base;
    if(uartid>8) return;
    base = g_uart[uartid].base;
    if(base==0) return;

    //compute using current value for clock, assuming OVER8=0
    //BAUD = fclk / (16 x DIV)
    //16 x DIV x BAUD = fclk
    // DIVfloat = fclk / (16 x BAUD) (DIV is a FLOAT)
    // DIVint   = (16 x fclk) / (16 x BAUD) (DIV is a INT with 4-bit frac part)
    // DIVint   = fclk / BAUD (DIV is a INT with 4-bit frac part)

    //divide
    baud = stm32l4_clock_get() / baud;
    //mask high bits
    baud &= 0xFFFF;
    putreg32(base + STM32_REGOFF_USART_BRR, baud);
}

void stm32l4_uart_send(uint32_t uartid, int data)
{
    uint32_t reg;
    if(uartid>8) return;
    reg = g_uart[uartid].base;
    if(reg==0) return;
    reg += STM32_REGOFF_USART_SR;
    //wait until the tx buffer is not empty
    while(!(getreg32(reg) & STM32_REGMASK_USART_SR_TXE));
    //send a single byte
    putreg32(g_uart[uartid].base + STM32_REGOFF_USART_DR, data&0xFF);
}

void stm32l4_uart_write_string(uint32_t uartid, const char *s)
{
    while(*s) stm32l4_uart_send(uartid, *s++);
}


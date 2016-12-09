#include <stdint.h>
#include <stddef.h>

#include "armv7m.h"
#include "bits/stm32l4_rcc.h"
#include "bits/stm32l4_uart.h"
#include "stm32l4_rcc.h"
#include "stm32l4_uart.h"

struct stm32l4_uart_s {
	uint32_t base;
	uint32_t ckenreg;
	uint32_t ckenbit;
};

#ifdef CONFIG_STM32L4_USART1
static const strct stm32l4_uart_s g_stm32l4_usart1 =
{
  .base    = STM32L4_REGBASE_USART1,
  .ckenreg = STM32L4_RCC_APB2ENR,
  .ckenbit = STM32L4_RCC_APB2ENR_USART1,
},
#endif
#ifdef CONFIG_STM32L4_USART2
static const strct stm32l4_uart_s g_stm32l4_usart2 =
{
  .base    = STM32L4_REGBASE_USART2,
  .ckenreg = STM32L4_RCC_APB1ENR,
  .ckenbit = STM32L4_RCC_APB1ENR_USART2,
},
#endif
#ifdef CONFIG_STM32L4_USART3
static const strct stm32l4_uart_s g_stm32l4_usart3 =
{
  .base = STM32L4_REGBASE_USART3,
  .ckenreg = STM32L4_RCC_APB1ENR,
  .ckenbit = STM32L4_RCC_ABP1ENR_USART3,
},
#endif
#ifdef CONFIG_STM32L4_UART4
static const strct stm32l4_uart_s g_stm32l4_uart4 =
{
  .base    = STM32L4_REGBASE_UART4,
  .ckenreg = STM32L4_REGOFF_RCC_APB1ENR,
  .ckenbit = STM32L4_REGOFF_RCC_APB1ENR_UART4,
},
#endif
#ifdef CONFIG_STM32L4_UART5
static const strct stm32l4_uart_s g_stm32l4_uart5 =
{
  .base    = STM32L4_REGBASE_UART5,
  .ckenreg = STM32L4_REGOFF_RCC_APB1ENR,
  .ckenbit = STM32L4_REGOFF_RCC_APB1ENR_UART5,
},
#endif

static const struct stm32l4_uart_s *g_stm32l4_uarts[] = {
#ifdef CONFIG_STM32L4_USART1
  &g_stm32l4_usart1,
#else
  NULL,
#endif
#ifdef CONFIG_STM32L4_USART2
  &g_stm32l4_usart2,
#else
  NULL,
#endif
#ifdef CONFIG_STM32L4_USART3
  &g_stm32l4_usart3,
#else
  NULL,
#endif
#ifdef CONFIG_STM32L4_UART4
  &g_stm32l4_uart4,
#else
  NULL,
#endif
#ifdef CONFIG_STM32L4_UART5
  &_stm32l4_uart5,
#else
  NULL,
#endif
};

/*----------------------------------------------------------------------------*/
static inline void stm32l4_uart_putreg(const struct stm32l4_uart_s *gpio, uint32_t regoff, uint32_t value)
{
  putreg32(gpio->base + regoff, value);
}

/*----------------------------------------------------------------------------*/
static inline uint32_t stm32l4_uart_getreg(const struct stm32l4_uart_s *gpio, uint32_t regoff)
{
  return getreg32(gpio->base + regoff);
}

/*----------------------------------------------------------------------------*/
void stm32l4_uart_earlysetup(void)
{
  /* Setup a basic UART so we can debug as soon as possible */
}

/*----------------------------------------------------------------------------*/
static inline void stm32l4_uart_updatereg(const struct stm32l4_uart_s *gpio, uint32_t regoff, uint32_t set, uint32_t clr)
{
  uint32_t val;
  val = getreg32(gpio->base + regoff);
  val &= ~clr;
  val |=  set;
  putreg32(gpio->base + regoff, val);
}

/*----------------------------------------------------------------------------*/
void stm32l4_uart_setup(uint32_t uartid)
{
  uint32_t base;
  uint32_t reg;
  uint32_t val;
  const struct stm32l4_uart_s *uart;

  if (uartid>(sizeof(g_stm32l4_uarts)/sizeof(g_stm32l4_uarts[0])))
    {
      return;
    }

  uart = g_stm32l4_uarts[uartid];
  if (uart==NULL)
    {
      return;
    }

  /* Enable clock to UART peripheral */

  reg = uart->ckenreg;
  val = getreg32(reg);
  val |= uart->ckenbit;
  putreg32(reg, val);

  /* Configure registers for a simple uart, 8 bits, 1 stop bit, no parity */

  //CR1: OVER8=0, UE=1, M=0, WAKE=0, PCE=0, no parity, no interrupts, RE=1, RWU=0
  stm32l4_uart_updatereg(uart, STM32L4_USART_CR1, STM32L4_USART_CR1_UE | STM32L4_USART_CR1_RE | STM32L4_USART_CR1_TE, 0xFFFF4000);

  //CR2: LINEN=0, STOP=00, CLKEN=0, no cpol, no cpha, no lbcl, no lin
  stm32l4_uart_updatereg(uart, STM32L4_USART_CR2, 0, 0xFFFF8090);

  //CR3: ONEBIT=0, no interrupts, CTSE=0, RTSE=0, no dma, SCEN=0, NACK=0, HDSEL=0, no irda
  stm32l4_uart_updatereg(uart, STM32L4_USART_CR3, 0, 0xFFFFF000);

}

/*----------------------------------------------------------------------------*/
/*
 * Fclk      baud      float     int(16times) hex   int part   frac part      approximated
 * 16 MHz    115200    8,68055   138          0x8A  8          10/16 = 0.625  8.625
 */
void stm32l4_uart_setbaud(uint32_t uartid, uint32_t baud)
{
  const struct stm32l4_uart_s *uart;

  if (uartid>(sizeof(g_stm32l4_uarts)/sizeof(g_stm32l4_uarts[0])))
    {
      return;
    }

  uart = g_stm32l4_uarts[uartid];
  if (uart==NULL)
    {
      return;
    }

  /*
   * Compute using current value for clock, assuming OVER8=0
   * BAUD = fclk / (16 x DIV)
   * 16 x DIV x BAUD = fclk
   * DIVfloat = fclk / (16 x BAUD) (DIV is a FLOAT)
   * DIVint   = (16 x fclk) / (16 x BAUD) (DIV is a INT with 4-bit frac part)
   * DIVint   = fclk / BAUD (DIV is a INT with 4-bit frac part)
   */

  /* Divide */
  baud = stm32l4_clock_get() / baud;

  /* Mask high bits */
  baud &= 0xFFFF;
  stm32l4_uart_putreg(uart, STM32L4_USART_BRR, baud);
}

/*----------------------------------------------------------------------------*/
void stm32l4_uart_send(uint32_t uartid, int data)
{
  const struct stm32l4_uart_s *uart;

  if (uartid>(sizeof(g_stm32l4_uarts)/sizeof(g_stm32l4_uarts[0])))
    {
      return;
    }

  uart = g_stm32l4_uarts[uartid];
  if (uart==NULL)
    {
      return;
    }

  /* Wait until the tx buffer is not empty */

  while(!(stm32l4_uart_getreg(uart, STM32L4_USART_ISR) & STM32L4_USART_ISR_TXE));

  /* Send a single byte */
  stm32l4_uart_putreg(uart, STM32L4_USART_TDR, data&0xFF);
}

/*----------------------------------------------------------------------------*/
void stm32l4_uart_write_string(uint32_t uartid, const char *s)
{
  while(*s)
    {
      stm32l4_uart_send(uartid, *s++);
    }
}


#ifndef __ARCH__ARMV6M__STM32F1__BITS__STM32F1__UART__H__
#define __ARCH__ARMV6M__STM32F1__BITS__STM32F1__UART__H__

/* Register offsets */

#define STM32F1_USART_SR   0x00
#define STM32F1_USART_DR   0x04
#define STM32F1_USART_BRR  0x08
#define STM32F1_USART_CR1  0x0C
#define STM32F1_USART_CR2  0x10
#define STM32F1_USART_CR3  0x14
#define STM32F1_USART_GPTR 0x18

/* Status Register */

#define USART_SR_PE     (1<<0) /* Parity Error */
#define USART_SR_FE     (1<<1) /* Framing Error */
#define USART_SR_NE     (1<<2) /* Noise Error */
#define USART_SR_ORE    (1<<3) /* Overrun Error */
#define USART_SR_IDLE   (1<<4) /* IDLE Line Detected */
#define USART_SR_RXNE   (1<<5) /* RX data reg not empty */
#define USART_SR_TC     (1<<6) /* Transmission complete */
#define USART_SR_TXE    (1<<7) /* TX data reg empty */
#define USART_SR_LBD    (1<<8) /* LIN break detection */
#define USART_SR_CTS    (1<<9) /* CTS flag */

/* Control Register 1 */

#define USART_CR1_SBK    (1<< 0) /* Send Break */
#define USART_CR1_RWU    (1<< 1) /* Receiver Wakeup (0 means active) */
#define USART_CR1_RE     (1<< 2) /* Receiver enable */
#define USART_CR1_TE     (1<< 3) /* Transmitter enable */
#define USART_CR1_IDLEIE (1<< 4) /* IDLE interrupt enable */
#define USART_CR1_RXNEIE (1<< 5) /* RXNE interrupt enable */
#define USART_CR1_TCIE   (1<< 6) /* TC interrupt enable */
#define USART_CR1_TXEIE  (1<< 7) /* TXE interrupt enable */
#define USART_CR1_PEIE   (1<< 8) /* PE interrupt enable */
#define USART_CR1_PS     (1<< 9) /* Parity Selection (1 means odd) */
#define USART_CR1_PCE    (1<<10) /* Parity Control Enable */
#define USART_CR1_WAKE   (1<<11) /* Wakeup method (1 means Address match) */
#define USART_CR1_M      (1<<12) /* Word Length (1 means 9 data bits) */
#define USART_CR1_UE     (1<<13) /* USART Enable */

/* Control Register 2 */

#define USART_CR2_ADD_SHIFT  0 /* Address of the USART node */
#define USART_CR2_ADD_MASK   (0x0F<<USART_CR2_ADD_SHIFT)
#define USART_CR2_LBDL       (1<< 5) /* LIN Break Detection Length */
#define USART_CR2_LBDIE      (1<< 6) /* LIN Break Detection interrupt enable */
#define USART_CR2_LBCL       (1<< 8) /* Last Bit Clock Pulse */
#define USART_CR2_CPHA       (1<< 9) /* Clock Phase */
#define USART_CR2_CPOL       (1<<10) /* Clock Polarity */
#define USART_CR2_CLKEN      (1<<11) /* Clock Enable */
#define USART_CR2_STOP_SHIFT 12 /* STOP bits */
#define USART_CR2_STOP_MASK  (3<<USART_CR2_STOP_SHIFT)
#define USART_CR2_STOP_1     (0<<USART_CR2_STOP_SHIFT)
#define USART_CR2_STOP_05    (1<<USART_CR2_STOP_SHIFT)
#define USART_CR2_STOP_2     (2<<USART_CR2_STOP_SHIFT)
#define USART_CR2_STOP_15    (3<<USART_CR2_STOP_SHIFT)
#define USART_CR2_LINEN      (1<<14) /* LIN Enable */

/* Control Register 3 */

#define USART_CR3_EIE   (1<<0) /* Error interrupt enable */
#define USART_CR3_IREN  (1<<1) /* IrDA mode Enable */
#define USART_CR3_IRLP  (1<<2) /* IrDA low-power */
#define USART_CR3_HDSEL (1<<3) /* Half-duplex selection */
#define USART_CR3_NACK  (1<<4) /* Smartcard NACK Enable */
#define USART_CR3_SCEN  (1<<5) /* Smartcard mode Enable */
#define USART_CR3_DMAR  (1<<6) /* DMA Enable Receiver */
#define USART_CR3_DMAT  (1<<7) /* DMA Enable Transmitter */
#define USART_CR3_RTSE  (1<<8) /* RTS Enable */
#define USART_CR3_CTSE  (1<< 9) /* CTS Enable */
#define USART_CR3_CTSIE (1<<10) /* CTS interrupt enable */

#endif /* __ARCH__ARMV6M__STM32F1__BITS__STM32F1__UART__H__ */

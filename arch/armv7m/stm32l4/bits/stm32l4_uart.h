#ifndef _ARCH_ARMV7M_STM32L4_BITS_STM32L4_UART_H_
#define _ARCH_ARMV7M_STM32L4_BITS_STM32L4_UART_H

//reg offsets
#define STM32L4_USART_CR1    0x00
#define STM32L4_USART_CR2    0x04
#define STM32L4_USART_CR3    0x08
#define STM32L4_USART_BRR    0x0C
#define STM32L4_USART_GTPR   0x10
#define STM32L4_USART_RTOR   0x14
#define STM32L4_USART_RQR    0x18
#define STM32L4_USART_ISR    0x1C
#define STM32L4_USART_ICR    0x20
#define STM32L4_USART_RDR    0x24
#define STM32L4_USART_TDR    0x28

/* Control Register 1 */

#define USART_CR1_UE            (1<<0)
#define USART_CR1_UESM          (1<<1)
#define USART_CR1_RE            (1<<2)
#define USART_CR1_TE            (1<<3)
#define USART_CR1_IDLEIE        (1<<4)
#define USART_CR1_RXNEIE        (1<<5)
#define USART_CR1_TCIE          (1<<6)
#define USART_CR1_TXEIE         (1<<7)
#define USART_CR1_PEIE          (1<<8)
#define USART_CR1_PS            (1<<9)
#define USART_CR1_PCE           (1<<10)
#define USART_CR1_WAKE          (1<<11)
#define USART_CR1_M0            (1<<12)
#define USART_CR1_MME           (1<<13)
#define USART_CR1_CMIE          (1<<14)
#define USART_CR1_OVER8         (1<<15)
#define USART_CR1_DEDT_SHIFT    16
#define USART_CR1_DEDT_MASK     (0x1F << USART_CR1_DEDT_SHIFT)
#define USART_CR1_DEAT_SHIFT    21
#define USART_CR1_DEAT_MASK     (0x1F << USART_CR1_DEDT_SHIFT)
#define USART_CR1_RTOIE         (1<<26)
#define USART_CR1_EOBIE         (1<<27)
#define USART_CR1_M1            (1<<28)

/* Control Register 2 */

#define USART_CR2_ADDM7         (1<<4)
#define USART_CR2_LBDL          (1<<5)
#define USART_CR2_LBDIE         (1<<6)
#define USART_CR2_LBCL          (1<<8)
#define USART_CR2_CPHA          (1<<9)
#define USART_CR2_CPOL          (1<<10)
#define USART_CR2_CLKEN         (1<<11)
#define USART_CR2_STOP_SHIFT    12
#define USART_CR2_STOP_MASK     (3 << USART_CR2_STOP_SHIFT)
#define USART_CR2_STOP_1        (0 << USART_CR2_STOP_SHIFT)
#define USART_CR2_STOP_05       (1 << USART_CR2_STOP_SHIFT)
#define USART_CR2_STOP_2        (2 << USART_CR2_STOP_SHIFT)
#define USART_CR2_STOP_15       (3 << USART_CR2_STOP_SHIFT)
#define USART_CR2_LINEN         (1<<14)
#define USART_CR2_SWAP          (1<<15)
#define USART_CR2_RXINV         (1<<16)
#define USART_CR2_TXINV         (1<<17)
#define USART_CR2_DATAINV       (1<<18)
#define USART_CR2_MSBFIRST      (1<<19)
#define USART_CR2_ABREN         (1<<20)
#define USART_CR2_ABRMOD_SHIFT  21
#define USART_CR2_ABRMOD_MASK   (3 << USART_CR2_ABRMOD_SHIFT)
#define USART_CR2_RTOEN         (1<<23)
#define USART_CR2_ADD_SHIFT     24
#define USART_CR2_ADD_MASK      (0xFF << USART_CR2_ADD_SHIFT)

/* Control Register 3 */

#define USART_CR3_EIE           (1<<0)
#define USART_CR3_IREN          (1<<1)
#define USART_CR3_IRLP          (1<<2)
#define USART_CR3_HDSEL         (1<<3)
#define USART_CR3_NACK          (1<<4)
#define USART_CR3_SCEN          (1<<5)
#define USART_CR3_DMAR          (1<<6)
#define USART_CR3_DMAT          (1<<7)
#define USART_CR3_RTSE          (1<<8)
#define USART_CR3_CTSE          (1<<9)
#define USART_CR3_CTSIE         (1<<10)
#define USART_CR3_ONEBIT        (1<<11)
#define USART_CR3_OVRDIS        (1<<12)
#define USART_CR3_DDRE          (1<<13)
#define USART_CR3_DEM           (1<<14)
#define USART_CR3_DEP           (1<<15)
#define USART_CR3_SCARCNT_SHIFT 17
#define USART_CR3_SCARCNT_MASK  (7 << USART_CR3_SCARCNT_SHIFT)
#define USART_CR3_WUS_SHIFT     20
#define USART_CR3_WUS_MASK      (3 << USART_CR3_WUS_SHIFT)
#define USART_CR3_WUFIE         (1<<22)
#define USART_CR3_UCESM         (1<<23)

#ifdef CONFIG_ARCH_CHIPFAMILY_STM32L4X3
#define USART_CR3_TCBGTIE       (1<<24)
#endif

/* Baud rate Register */

#define USART_BRR_SHIFT 0
#define USART_BRR_MASK  (0xFFFF << USART_BRR)SHIFT)

/* Guard time and prescaler Register */

#define USART_GTPR_PSC_SHIFT    0
#define USART_GTPR_PSC_MASK     (0xFF << USART_GTPR_PSC_SHIFT)
#define USART_GTPR_GT_SHIFT     8
#define USART_GTPR_GT_MASK      (0xFF << USART_GTPR_GT_SHIFT)

/* Interrupt and Status Register */
#define USART_ISR_PE            (1<< 0)
#define USART_ISR_FE            (1<< 1)
#define USART_ISR_NF            (1<< 2)
#define USART_ISR_ORE           (1<< 3)
#define USART_ISR_IDLE          (1<< 4)
#define USART_ISR_RXNE          (1<< 5)
#define USART_ISR_TC            (1<< 6)
#define USART_ISR_TXE           (1<< 7)
#define USART_ISR_LBDF          (1<< 8)
#define USART_ISR_CTSIF         (1<< 9)
#define USART_ISR_CTS           (1<<10)
#define USART_ISR_RTOF          (1<<11)
#define USART_ISR_EOBF          (1<<12)
#define USART_ISR_ABRE          (1<<14)
#define USART_ISR_ABRF          (1<<15)
#define USART_ISR_BUSY          (1<<16)
#define USART_ISR_CMF           (1<<17)
#define USART_ISR_SBKF          (1<<18)
#define USART_ISR_RWU           (1<<19)
#define USART_ISR_WUF           (1<<20)
#define USART_ISR_TEACK         (1<<21)
#define USART_ISR_REACK         (1<<22)
//stm32l4x3
#ifdef CONFIG_ARCH_CHIPFAMILY_STM32L4X3
#define USART_ISR_TCBGT         (1<<25)
#endif

/* Interrupt flag Clean Register */
#define USART_ICR_PECF          (1<< 0)
#define USART_ICR_FECF          (1<< 1)
#define USART_ICR_NCF           (1<< 2)
#define USART_ICR_ORECF         (1<< 3)
#define USART_ICR_IDLECF        (1<< 4)
#define USART_ICR_TCCF          (1<< 6)
#ifdef CONFIG_ARCH_CHIPFAMILY_STM32L4X3
#define USART_ICR_TCBGTCF       (1<< 7)
#endif
#define USART_ICR_LBDCF         (1<< 8)
#define USART_ICR_CTSCF         (1<< 9)
#define USART_ICR_RTOCF         (1<<11)
#define USART_ICR_EOBCF         (1<<12)
#define USART_ICR_CMCF          (1<<17)
#define USART_ICR_WUCF          (1<<20)

#endif /* _ARCH_ARMV7M_STM32L4_BITS_STM32L4_UART_H_*/


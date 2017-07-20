#ifndef _ARCH_ARMV7M_STM32L4_BITS_STM32L4_SPI_H_
#define _ARCH_ARMV7M_STM32L4_BITS_STM32L4_SPI_H_

//reg offsets
#define STM32L4_SPI_CR1              0x00
#define STM32L4_SPI_CR2              0x04
#define STM32L4_SPI_SR               0x08
#define STM32L4_SPI_DR               0x0C
#define STM32L4_SPI_CRCPR            0x10
#define STM32L4_SPI_RXCRCR           0x14
#define STM32L4_SPI_TXCRCR           0x18

//bits values
#define SPI_CR1_BIDIMODE    (1<<15)
#define SPI_CR1_BIDIOE      (1<<14)
#define SPI_CR1_CRCEN       (1<<13)
#define SPI_CR1_CRCNEXT     (1<<12)
#define SPI_CR1_CRCL        (1<<11)
#define SPI_CR1_RXONLY      (1<<10)
#define SPI_CR1_SSM         (1<<9)
#define SPI_CR1_SSI         (1<<8)
#define SPI_CR1_LSBFIRST    (1<<7)
#define SPI_CR1_SPE         (1<<6)
#define SPI_CR1_BR_SHIFT    3
#define SPI_CR1_BR_MASK     (7<<SPI_CR1_BR_SHIFT)
#define SPI_CR1_MSTR        (1<<2)
#define SPI_CR1_CPOL        (1<<1)
#define SPI_CR1_CPHA        (1<<0)

#define SPI_CR2_LDMA_TX     (1<<14)
#define SPI_CR2_LDMA_RX     (1<<13)
#define SPI_CR2_FRXTH       (1<<12)
#define SPI_CR2_DS_SHIFT    8
#define SPI_CR2_DS_MASK     (15<<SPI_CR2_DS_SHIFT)
#define SPI_CR2_TXEIE       (1<<7)
#define SPI_CR2_RXNEIE      (1<<6)
#define SPI_CR2_ERRIE       (1<<5)
#define SPI_CR2_FRF         (1<<4)
#define SPI_CR2_NSSP        (1<<3)
#define SPI_CR2_SSOE        (1<<2)
#define SPI_CR2_TXDMAEN     (1<<1)
#define SPI_CR2_RXDMAEN     (1<<0)

#define SPI_SR_FTLVL_SHIFT  11
#define SPI_SR_FTLVL_MASK   (3<<SPI_SR_FTLVL_SHIFT)
#define SPI_SR_FRLVL_SHIFT  9
#define SPI_SR_FRLVL_MASK   (3<<SPI_SR_FRLVL_SHIFT)
#define SPI_SR_FRE          (1<<8)
#define SPI_SR_BSY          (1<<7)
#define SPI_SR_OVR          (1<<6)
#define SPI_SR_MODF         (1<<5)
#define SPI_SR_CRCERR       (1<<4)
#define SPI_SR_TXE          (1<<1)
#define SPI_SR_RXNE         (1<<0)

#endif /* _ARCH_ARMV7M_STM32L4_BITS_STM32L4_SPI_H_ */

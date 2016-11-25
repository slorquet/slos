#include <stdint.h>

#include "armv7m.h"
#include "stm32f4_rcc.h"
#include "stm32f4_spi.h"
#include "bits/stm32f4_spi.h"

struct spi_params {
	uint32_t base;
	uint32_t ckenreg;
	uint32_t ckenbit;
};

static const struct spi_params g_spi[] = {
#ifdef STM32F4_HAVE_SPI_1
    [STM32F4_SPI_1] = {0x40013000, STM32F4_REG_RCC_APB2ENR, 12},
#endif
#ifdef STM32F4_HAVE_SPI_2
    [STM32F4_SPI_2] = {0x40003800, STM32F4_REG_RCC_APB1ENR, 14},
#endif
#ifdef STM32F4_HAVE_SPI_3
    [STM32F4_SPI_3] = {0x40003C00, STM32F4_REG_RCC_APB1ENR, 15},
#endif
#ifdef STM32F4_HAVE_SPI_4
    [STM32F4_SPI_4] = {0x40013400, STM32F4_REG_RCC_APB2ENR, 13},
#endif
#ifdef STM32F4_HAVE_SPI_5
    [STM32F4_SPI_5] = {0x40015000, STM32F4_REG_RCC_APB2ENR, 20},
#endif
};

void stm32f4_spi_init(uint32_t spiid, uint32_t flags)
{
    uint32_t base;
    uint32_t reg;
    uint32_t val;

    if(spiid>STM32F4_SPI_5) return;
    base = g_spi[spiid].base;
    if(base==0) return;

    //Enable clock to SPI peripheral
    reg = g_spi[spiid].ckenreg;
    val = getreg32(reg);
    val |= (1<<g_spi[spiid].ckenbit);
    putreg32(reg, val);

    //configure registers for a simple spi, 8 bits values

    //CR1: BIDI=0, no bidioe, CRCEN=0, CRCNEXT=0, DFF=0, RXONLY=0, SSM=1, SSI=1 (software SS), lsbfirst as given, SPE=1, BR as given, MSTR=1, cpol, cpha as given
    reg  = base + STM32F4_REGOFF_SPI_CR1;
    val  = STM32F4_REGMASK_SPI_CR1_SPE | STM32F4_REGMASK_SPI_CR1_MSTR | STM32F4_REGMASK_SPI_CR1_SSM | STM32F4_REGMASK_SPI_CR1_SSI;
    val |= ((flags & STM32F4_SPI_FLAGS_MASK_LSBFIRST) >> STM32F4_SPI_FLAGS_SHIFT_LSBFIRST) ? STM32F4_REGMASK_SPI_CR1_LSBFIRST : 0;
    val |= ((flags & STM32F4_SPI_FLAGS_MASK_CPOL) >> STM32F4_SPI_FLAGS_SHIFT_CPOL) ? STM32F4_REGMASK_SPI_CR1_CPOL : 0;
    val |= ((flags & STM32F4_SPI_FLAGS_MASK_CPHA) >> STM32F4_SPI_FLAGS_SHIFT_CPHA) ? STM32F4_REGMASK_SPI_CR1_CPHA : 0;
    val |= ((flags & STM32F4_SPI_FLAGS_MASK_BAUDDIV) >> STM32F4_SPI_FLAGS_SHIFT_BAUDDIV) << STM32F4_REGSHIFT_SPI_CR1_BR;
    putreg32(reg, val);

    //CR2: no ints, FRF=0, SSOE=0, no DMA
    putreg32(base + STM32F4_REGOFF_SPI_CR2, 0x00000000);

    //I2SCFGR: No I2S, all zero.
    putreg32(base + STM32F4_REGOFF_SPI_I2SCFGR, 0x00000000);

}

void stm32f4_spi_transac8_base(uint32_t spiid, uint32_t len, uint8_t *mosi, uint8_t *miso)
{
  int index=0;
  uint8_t data;
  uint32_t reg,sreg;

  if(spiid>STM32F4_SPI_5) return;
  reg = g_spi[spiid].base;
  if(reg==0) return;
  sreg = reg + STM32F4_REGOFF_SPI_SR;
  reg += STM32F4_REGOFF_SPI_DR;

  while(index<len)
    {
      if(mosi)
        {
          data = mosi[index];
        }
      else
        {
          data = 0xFF;
        }

      while( !(getreg32(sreg) & STM32F4_REGMASK_SPI_SR_TXE) );
      putreg32(reg, data);
      while( !(getreg32(sreg) & STM32F4_REGMASK_SPI_SR_RXNE) );
      data = getreg32(reg);

      if(miso)
        {
          miso[index] = data;
        }

      data = getreg32(sreg);
      (void) data;

      index++;
    }
}

/*this version seems optimized but is not modular*/
void stm32f4_spi_transac8(uint32_t spiid, uint32_t len, uint8_t *mosi, uint8_t *miso)
{
    uint32_t reg,sreg;
    uint32_t txid=0,rxid=0;
    uint32_t data;
    if(spiid>STM32F4_SPI_5) return;
    reg = g_spi[spiid].base;
    if(reg==0) return;
    sreg = reg + STM32F4_REGOFF_SPI_SR;
    reg += STM32F4_REGOFF_SPI_DR;
    //see RM0090 (docid 018909) page 871, figure 253
    //tx write and rx read must be managed concurrently,
    //because the tx buffer is empty before the char is sent, so we can write in advance.
    while(rxid<len) {
        uint32_t stat = getreg32(sreg);
        if( txid<len && (stat & STM32F4_REGMASK_SPI_SR_TXE) ) {
            if(mosi) {
                data=mosi[txid];
            } else {
                data=0xFF;
            }
            putreg32(reg, data); //this clears TXE
            txid++;
        }
        //as soon as RXNE is set, read and store
        stat = getreg32(sreg);
        if( rxid<len && (stat & STM32F4_REGMASK_SPI_SR_RXNE)) {
            data = getreg32(reg); //this clears TXNE
            if(miso) {
                miso[rxid] = data;
            }
            rxid++;
        }
    }
    //All data was now sent, wait until the spi transaction is not busy anymore
    while( (getreg32(sreg) & STM32F4_REGMASK_SPI_SR_BSY) );

}


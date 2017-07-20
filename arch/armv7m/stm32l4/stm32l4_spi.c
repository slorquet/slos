#include <stddef.h>
#include <stdint.h>
#include <errno.h>

#include "armv7m.h"
#include "stm32l4_rcc.h"
#include "stm32l4_gpio.h"
#include "stm32l4_spi.h"
#include "bits/irq.h"
#include "bits/stm32l4_periphs.h"
#include "bits/stm32l4_spi.h"

/*==============================================================================
 * Types
 *==============================================================================
 */

struct stm32l4_spiparams_s /* Stored in Flash */
{
  uint32_t base;
  uint32_t ckenreg;
  uint32_t ckenbit;
  uint32_t misopin;
  uint32_t mosipin;
  uint32_t sclkpin;
  uint8_t  irq;    /* irq line */
};

struct stm32l4_spi_s /* Stored in RAM */
{
  struct spi_master_s master; /* Must be the first field */
  const struct stm32l4_spiparams_s *params;
  uint8_t speedbits;
};

/*==============================================================================
 * Function Prototypes
 *==============================================================================
 */

struct spi_master_s *stm32l4_spi_init(uint32_t spiid);
int stm32l4_spi_transac(struct spi_master_s *dev, struct spi_transac_s *transac);

/*==============================================================================
 * Variables and constants
 *==============================================================================
 */

static const struct spi_ops_s g_stm32l4_spiops =
{
  .transac = stm32l4_spi_transac
};

#ifdef CONFIG_STM32L4_SPI1
static const struct stm32l4_spiparams_s g_stm32l4_spi1params =
{
  .base    = STM32L4_REGBASE_SPI1,
  .ckenreg = STM32L4_RCC_APB2ENR,
  .ckenbit = RCC_APB2ENR_SPI1,
#if defined(STM32L4_SPI1_MISO_NONE)
  .misopin = 0,
#elif defined(STM32L4_SPI1_MISO_A6)
  .misopin = GPIO_PORT_A | GPIO_PIN_6 | GPIO_MODE_ALT | GPIO_ALT_5,
#elif defined(STM32L4_SPI1_MISO_B4)
  .misopin = GPIO_PORT_B | GPIO_PIN_4 | GPIO_MODE_ALT | GPIO_ALT_5,
#elif defined(STM32L4_SPI1_MISO_E14)
  .misopin = GPIO_PORT_E | GPIO_PIN_14 | GPIO_MODE_ALT | GPIO_ALT_5,
#elif defined(STM32L4_SPI1_MISO_G3)
  .misopin = GPIO_PORT_G | GPIO_PIN_3 | GPIO_MODE_ALT | GPIO_ALT_5,
#else
#error bad definition for SPI1 MISO
#endif

#if defined(STM32L4_SPI1_MOSI_NONE)
  .mosipin = 0,
#elif defined(STM32L4_SPI1_MOSI_A7)
  .mosipin = GPIO_PORT_A | GPIO_PIN_7 | GPIO_MODE_ALT | GPIO_ALT_5,
#elif defined(STM32L4_SPI1_MOSI_B5)
  .mosipin = GPIO_PORT_B | GPIO_PIN_5 | GPIO_MODE_ALT | GPIO_ALT_5,
#elif defined(STM32L4_SPI1_MOSI_E15)
  .mosipin = GPIO_PORT_E | GPIO_PIN_15 | GPIO_MODE_ALT | GPIO_ALT_5,
#elif defined(STM32L4_SPI1_MOSI_G4)
  .mosipin = GPIO_PORT_G | GPIO_PIN_4 | GPIO_MODE_ALT | GPIO_ALT_5,
#else
#error bad definition for SPI1 MOSI
#endif

#if defined(STM32L4_SPI1_SCLK_NONE)
  .sclkpin = 0,
#elif defined(STM32L4_SPI1_SCLK_A5)
  .sclkpin = GPIO_PORT_A | GPIO_PIN_5 | GPIO_MODE_ALT | GPIO_ALT_5,
#elif defined(STM32L4_SPI1_SCLK_B3)
  .sclkpin = GPIO_PORT_B | GPIO_PIN_3 | GPIO_MODE_ALT | GPIO_ALT_5,
#elif defined(STM32L4_SPI1_SCLK_E13)
  .sclkpin = GPIO_PORT_E | GPIO_PIN_13 | GPIO_MODE_ALT | GPIO_ALT_5,
#elif defined(STM32L4_SPI1_SCLK_G2)
  .sclkpin = GPIO_PORT_G | GPIO_PIN_2 | GPIO_MODE_ALT | GPIO_ALT_5,
#else
#error bad definition for SPI1 SCLK
#endif

  .irq     = STM32L4_IRQ_SPI1
};

static struct stm32l4_spi_s g_stm32l4_spi1 =
{
  .master =
    {
      .ops          = &g_stm32l4_spiops,
    },
  .params = &g_stm32l4_spi1params,
};
#endif

#ifdef CONFIG_STM32L4_SPI2
static const struct stm32l4_spiparams_s g_stm32l4_spi2params =
{
  .base    = STM32L4_REGBASE_SPI2,
  .ckenreg = STM32L4_RCC_APB1ENR,
  .ckenbit = RCC_APB1ENR_SPI2,
  .misopin = 0,
  .mosipin = 0,
  .sclkpin = 0,
  .irq     = STM32L4_IRQ_SPI2
};

static struct stm32l4_spi_s g_stm32l4_spi2 =
{
  .master =
    {
      .ops          = &g_stm32l4_spiops,
    },
  .params = &g_stm32l4_spi2params,
};
#endif

#ifdef CONFIG_STM32L4_SPI3
static const struct stm32l4_spiparams_s g_stm32l4_spi3params =
{
  .base    = STM32L4_REGBASE_SPI3,
  .ckenreg = STM32L4_RCC_APB1ENR,
  .ckenbit = RCC_APB1ENR_SPI3,
  .misopin = 0,
  .mosipin = 0,
  .sclkpin = 0,
  .irq     = STM32L4_IRQ_SPI3
};

static struct stm32l4_spi_s g_stm32l4_spi3 =
{
  .master =
    {
      .ops          = &g_stm32l4_spiops,
    },
  .params = &g_stm32l4_spi3params,
};
#endif

static struct stm32l4_spi_s * g_stm32l4_spis[] = {
#ifdef CONFIG_STM32L4_SPI1
  &g_stm32l4_spi1,
#endif
#ifdef CONFIG_STM32L4_SPI2
  &g_stm32l4_spi2,
#endif
#ifdef CONFIG_STM32L4_SPI3
  &g_stm32l4_spi3,
#endif
};

/* Create an enum to count uarts, because sizeof(uarts[0]) will not work if there are no uarts */
enum
{
#ifdef CONFIG_STM32L4_SPI1
  STM32L4_INDEX_SPI1,
#endif
#ifdef CONFIG_STM32L4_SPI2
  STM32L4_INDEX_SPI2,
#endif
#ifdef CONFIG_STM32L4_SPI3
  STM32L4_INDEX_SPI3,
#endif
  STM32L4_SPICOUNT
};

#if 0
void stm32l4_spi_transac8_base(uint32_t spiid, uint32_t len, uint8_t *mosi, uint8_t *miso)
{
  int index=0;
  uint8_t data;
  uint32_t reg,sreg;

  if(spiid>STM32L4_SPI_5) return;
  reg = g_spi[spiid].base;
  if(reg==0) return;
  sreg = reg + STM32L4_REGOFF_SPI_SR;
  reg += STM32L4_REGOFF_SPI_DR;

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

      while( !(getreg32(sreg) & STM32L4_REGMASK_SPI_SR_TXE) );
      putreg32(reg, data);
      while( !(getreg32(sreg) & STM32L4_REGMASK_SPI_SR_RXNE) );
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
#endif

#if 0
/*this version seems optimized but is not modular*/
void stm32l4_spi_transac8(uint32_t spiid, uint32_t len, uint8_t *mosi, uint8_t *miso)
{
    uint32_t reg,sreg;
    uint32_t txid=0,rxid=0;
    uint32_t data;
    if(spiid>STM32L4_SPI_5) return;
    reg = g_spi[spiid].base;
    if(reg==0) return;
    sreg = reg + STM32L4_REGOFF_SPI_SR;
    reg += STM32L4_REGOFF_SPI_DR;
    //see RM0090 (docid 018909) page 871, figure 253
    //tx write and rx read must be managed concurrently,
    //because the tx buffer is empty before the char is sent, so we can write in advance.
    while(rxid<len) {
        uint32_t stat = getreg32(sreg);
        if( txid<len && (stat & STM32L4_REGMASK_SPI_SR_TXE) ) {
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
        if( rxid<len && (stat & STM32L4_REGMASK_SPI_SR_RXNE)) {
            data = getreg32(reg); //this clears TXNE
            if(miso) {
                miso[rxid] = data;
            }
            rxid++;
        }
    }
    //All data was now sent, wait until the spi transaction is not busy anymore
    while( (getreg32(sreg) & STM32L4_REGMASK_SPI_SR_BSY) );

}
#endif

/*----------------------------------------------------------------------------*/
static inline uint32_t stm32l4_spi_getreg(const struct stm32l4_spi_s *spi, uint32_t regoff)
{
  return getreg32(spi->params->base + regoff);
}

/*----------------------------------------------------------------------------*/
static inline void stm32l4_spi_putreg(const struct stm32l4_spi_s *spi, uint32_t regoff, uint32_t value)
{
  putreg32(spi->params->base + regoff, value);
}

/*----------------------------------------------------------------------------*/
static inline void stm32l4_spi_updatereg(const struct stm32l4_spi_s *spi, uint32_t regoff, uint32_t setbits, uint32_t clrbits)
{
  updatereg32(spi->params->base + regoff, setbits, clrbits);
}

/*----------------------------------------------------------------------------*/
static void stm32l4_spi_lock(struct stm32l4_spi_s *spi)
{
}

/*----------------------------------------------------------------------------*/
static void stm32l4_spi_unlock(struct stm32l4_spi_s *spi)
{
}

/*----------------------------------------------------------------------------*/
static int stm32l4_spi_setspeed(struct stm32l4_spi_s *spi, uint32_t speed)
{
  uint32_t bauddiv;
  uint32_t pclk;
  struct stm32l4_clocks_s *clocks;
  int bits;

  if(spi->master.speed == speed)
    {
      return 0;
    }

  clocks = stm32l4_clock_getinfo();

  if(spi->params->irq == STM32L4_IRQ_SPI1)
    {
      pclk = clocks->pclk2; /* SPI1 on APB2 */
    }
  else
    {
      pclk = clocks->pclk1; /* SPI2/3 are on APB1 */
    }

  bauddiv = speed / pclk;
  bits = 0;

  while ( !(bauddiv & 1) )
    {
      bauddiv >>= 1;
      bits     += 1;
    }

  if(bits>7) bits = 7;

  if(spi->speedbits != bits)
    {
      return 0;
    }

  stm32l4_spi_updatereg(spi, STM32L4_SPI_CR1, bits<<SPI_CR1_BR_SHIFT, SPI_CR1_BR_MASK);

  spi->speedbits = bits;
  spi->master.speed = pclk / (1<<bits);

  return 0;
}

/*----------------------------------------------------------------------------*/
static int stm32l4_spi_setwordsize(struct stm32l4_spi_s *spi, uint8_t size)
{
  if(spi->master.bits == size)
    {
      return 0;
    }

  if(size<4 || size>16)
    {
      return -EINVAL;
    }

  size -= 1;

  stm32l4_spi_updatereg(spi, STM32L4_SPI_CR2, size << SPI_CR2_DS_SHIFT, SPI_CR2_DS_MASK);

  spi->master.bits = size;
  return 0;
}

/*----------------------------------------------------------------------------*/
static int stm32l4_spi_setbitorder(struct stm32l4_spi_s *spi, bool msbfirst)
{
  if(spi->master.msbfirst == msbfirst)
    {
      return 0;
    }

  if(msbfirst)
    {
      stm32l4_spi_updatereg(spi, STM32L4_SPI_CR1, 0, SPI_CR1_LSBFIRST);
    }
  else
    {
      stm32l4_spi_updatereg(spi, STM32L4_SPI_CR1, SPI_CR1_LSBFIRST, 0);
    }

  spi->master.msbfirst = msbfirst;
  return 0;
}

/*----------------------------------------------------------------------------*/
static int stm32l4_spi_setbusmode(struct stm32l4_spi_s *spi, bool cpol, bool cpha)
{
  if(spi->master.cpol == cpol)
    {
      goto cpha;
    }
  if(cpol)
    {
      stm32l4_spi_updatereg(spi, STM32L4_SPI_CR1, 0, SPI_CR1_CPOL);
    }
  else
    {
      stm32l4_spi_updatereg(spi, STM32L4_SPI_CR1, SPI_CR1_CPOL, 0);
    }
  spi->master.cpol = cpol;

cpha:
  if(spi->master.cpha == cpha)
    {
      return 0;
    }
  if(cpha)
    {
      stm32l4_spi_updatereg(spi, STM32L4_SPI_CR1, 0, SPI_CR1_CPHA);
    }
  else
    {
      stm32l4_spi_updatereg(spi, STM32L4_SPI_CR1, SPI_CR1_CPHA, 0);
    }
  spi->master.cpha = cpha;

  return 0;
}

/*----------------------------------------------------------------------------*/
static int stm32l4_spi_transfer(struct stm32l4_spi_s *spi, void *txbuf, void *rxbuf, uint32_t len)
{
  return 0;
}

/*----------------------------------------------------------------------------*/
int stm32l4_spi_transac(struct spi_master_s *dev, struct spi_transac_s *transac)
{
  int i;
  int ret = 0;
  struct stm32l4_spi_s *spi = (struct stm32l4_spi_s *)dev;

  stm32l4_spi_lock(spi);

  ret = stm32l4_spi_setspeed   (spi, transac->speed);
  if (ret != 0) goto unlock;
  ret = stm32l4_spi_setwordsize(spi, transac->wordsize);
  if (ret != 0) goto unlock;
  ret = stm32l4_spi_setbitorder(spi, (transac->options & SPI_ORDER_MSBFIRST) == SPI_ORDER_MSBFIRST);
  if (ret != 0) goto unlock;
  ret = stm32l4_spi_setbusmode (spi, (transac->options & SPI_CPOL_1) == SPI_CPOL_1,
                                     (transac->options & SPI_CPHA_1) == SPI_CPHA_1);
  if (ret != 0) goto unlock;

  for (i=0; i < transac->msgcount; i++)
    {
      ret = stm32l4_spi_transfer(spi, transac->msgs[i].txbuf, transac->msgs[i].rxbuf, transac->msgs[i].len);
      if (ret != 0) goto unlock;
    }

unlock:
  stm32l4_spi_unlock(spi);
  return ret;
}

/*----------------------------------------------------------------------------*/
struct spi_master_s *stm32l4_spi_init(uint32_t spiid)
{
  uint32_t base;
  uint32_t reg;
  uint32_t val;
  struct stm32l4_spi_s *spi;

  switch(spiid)
    {
#ifdef CONFIG_STM32L4_SPI1
      case 1: spi = &g_stm32l4_spi1; break;
#endif
#ifdef CONFIG_STM32L4_SPI2
      case 2: spi = &g_stm32l4_spi2; break;
#endif
#ifdef CONFIG_STM32L4_SPI3
      case 3: spi = &g_stm32l4_spi3; break;
#endif
      default:
        return NULL;
    }

  /* Configure GPIOs */

  if (spi->params->mosipin)
    {
      stm32l4_gpio_init(spi->params->mosipin);
    }
  if (spi->params->misopin)
    {
      stm32l4_gpio_init(spi->params->misopin);
    }
  if (spi->params->sclkpin)
    {
      stm32l4_gpio_init(spi->params->sclkpin);
    }

  /* Default settings */

  spi->speedbits = 0;

  /* Enable clock to SPI peripheral */

  updatereg32(STM32L4_REGBASE_RCC + spi->params->ckenreg, spi->params->ckenbit, 0);

  /* Define common config, except speed, word size, bit order, but mode */

  //CR1: BIDI=0, no bidioe, CRCEN=0, CRCNEXT=0, DFF=0, RXONLY=0, SSM=1, SSI=1 (software SS), lsbfirst as given, SPE=1, BR as given, MSTR=1, cpol, cpha as given
  stm32l4_spi_updatereg(spi, STM32L4_SPI_CR1,
    SPI_CR1_SPE | SPI_CR1_MSTR | SPI_CR1_SSM | SPI_CR1_SSI,
    SPI_CR1_BIDIMODE | SPI_CR1_BIDIOE | SPI_CR1_CRCEN | SPI_CR1_CRCNEXT | SPI_CR1_RXONLY);

  //CR2: no ints, FRF=0, SSOE=0, no DMA
  stm32l4_spi_putreg(spi, STM32L4_SPI_CR2, 0x00000000);

  /* Return instance */
  return &spi->master;

}


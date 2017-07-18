#ifndef __SLOS__SPIMASTER__H__
#define __SLOS__SPIMASTER__H__

/* SPI master driver */

#define SPI_CPHA_0         0x00
#define SPI_CPHA_1         0x01
#define SPI_CPOL_0         0x00
#define SPI_CPOL_1         0x02
#define SPI_ORDER_MSBFIRST 0x00
#define SPI_ORDER_LSBFIRST 0x04

struct spi_msg_s
{
  void *   txbuf; /* Buffer for transmitted data */
  void *   rxbuf; /* Buffer for received data */
  uint32_t len; /* Number of bytes to exchange at this step */
};

struct spi_transac_s
{
  uint32_t          speed;    /* Speed in Hz to use for these steps */
  uint8_t           wordsize; /* bits per frame to use for these steps */
  uint8_t           options;  /* Transfer options for these steps */
  int               msgcount;
  struct spi_msg_s *msgs;
};

struct spi_master_s;

struct spi_ops_s
{
  int (*transac)(struct spi_master_s *dev, struct spi_transac_s *transac);
};

struct spi_master_s
{
  struct spi_ops_s *ops;
  uint32_t speed; /* current speed */
  uint8_t  bits;
  uint8_t  options;
};

#endif /* __SLOS__STDIO__H__ */

#ifndef __INCLUDE__SLOS__UART__H__
#define __INCLUDE__SLOS__UART__H__

struct uart_s;

struct uart_ops_s
{
  int (*init)(struct uart_s *uart); /*setup baud rate and port params, enable uart*/
  int (*fini)(struct uart_s *uart); /*disable uart*/
  int (*write)(struct uart_s *uart, const uint8_t *buf, int len); /*write some bytes to buffer*/
  int (*flush)(struct uart_s *uart); /*finish buffer transmission*/
  int (*avail)(struct uart_s *uart); /*tell how many bytes can be read*/
  int (*read )(struct uart_s *uart, uint8_t *buf, int len); /*read some bytes from port*/
  int (*ioctl)(struct uart_s *uart, int command, void* params); /*control port details*/
};

struct uart_s
{
  const struct uart_ops_s *ops;
  uint32_t baudrate;
  uint8_t parity;
  uint8_t databits;
  uint8_t stopbits;
};

#endif /* __INCLUDE__SLOS__UART__H__ */


#ifndef __TERMIOS__H__
#define __TERMIOS__H__

#include <stdint.h>

typedef uint32_t tcflag_t;
typedef char cc_t;
typedef uint32_t speed_t;

#define NCCS 9

enum
{
  VEOF,
  VEOL,
  VERASE,
  VINTR,
  VKILL,
  VQUIT,
  VSTART,
  VSTOP,
  VSUSP
};

/* Input modes */

#define BRKINT    (1<< 0) /* Signal interrupt on break. */
#define ICRNL     (1<< 1) /* Map CR to NL on input. */
#define IGNBRK    (1<< 2) /* Ignore break condition. */
#define IGNCR     (1<< 3) /* Ignore CR. */
#define IGNPAR    (1<< 4) /* Ignore characters with parity errors. */
#define INLCR     (1<< 5) /* Map NL to CR on input. */
#define INPCK     (1<< 6) /* Enable input parity check. */
#define ISTRIP    (1<< 7) /* Strip character. */
#define IXANY     (1<< 8) /* Enable any character to restart output. */
#define IXOFF     (1<< 9) /* Enable start/stop input control. */
#define IXON      (1<<10) /* Enable start/stop output control. */
#define PARMRK    (1<<11) /* Mark parity errors. */

/* Output modes */

#define OPOST    (1<<0) /* Post-process output. */
#define ONLCR    (1<<1) /* Map NL to CR-NL on output. */
#define OCRNL    (1<<2) /* Map CR to NL on output. */
#define ONLRET   (1<<3) /* NL performs CR function. */

/* Baud */

#define B0           0 /* Hang up*/
#define B50         50
#define B75         75
#define B110       110
#define B134       134 /* officially 134.5 */
#define B150       150
#define B200       200
#define B300       300
#define B600       600
#define B1200     1200
#define B1800     1800
#define B2400     2400
#define B4800     4800
#define B9600     9600
#define B19200   19200
#define B38400   38400 

#define B57600   57600
#define B115200 115200

/* Local */

#define CSIZE 0x00000003L
#define CS5   0x00000000L
#define CS6   0x00000001L
#define CS7   0x00000002L
#define CS8   0x00000003L

#define CSTOPB 0x00000004 /* Send two stop bits, else one. */
#define CREAD  0x00000008 /* Enable receiver. */
#define PARENB 0x00000010 /* Parity enable. */
#define PARODD 0x00000020 /* Odd parity, else even. */
#define HUPCL  0x00000040 /* Hang up on last close. */
#define CLOCAL 0x00000080 /* Ignore modem status lines. */

struct termios
{
  tcflag_t  c_iflag; /* Input modes */
  tcflag_t  c_oflag; /* Output modes */
  tcflag_t  c_cflag; /* Control modes */
  tcflag_t  c_lflag; /* Local modes */
  cc_t      c_cc[NCCS];
  /* Private fields */
  speed_t   c_baud;
};

#endif /* __TERMIOS__H__ */

include $(TOPDIR)/.config
include $(TOPDIR)/Make.defs

CSRCS=board_start.c


CFLAGS+=-I..
CFLAGS+=-I../include
CFLAGS+=-I$(TOPDIR)/arch/$(CONFIG_ARCH)/include
CFLAGS+=-I$(TOPDIR)/arch/$(CONFIG_ARCH)/$(CONFIG_ARCH_CHIP_FAMILY)

install: $(OBJS) $(MAINOBJ) 
	$(AR) rcs $(TOPDIR)/libs/libboard.a $(OBJS)

clean:
	$(RM) $(OBJS)


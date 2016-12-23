-include $(TOPDIR)/.config
include $(TOPDIR)/tools/Dequote.mk

-include $(TOPDIR)/Make.defs

CSRCS:=

CFLAGS+=-isystem $(TOPDIR)/include
#CFLAGS+=-Iarch/$(CONFIG_ARCH)/include
#CFLAGS+=-Iarch/$(CONFIG_ARCH)/$(CONFIG_ARCH_CHIP_FAMILY)

include string/Make.defs

install: $(OBJS)
	$(AR) rcs $(TOPDIR)/libc.a $(OBJS)

clean:
	$(RM) $(OBJS)


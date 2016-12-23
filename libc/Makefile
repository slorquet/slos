-include $(TOPDIR)/.config
include $(TOPDIR)/tools/Dequote.mk
-include $(TOPDIR)/Make.defs

CSRCS:=
include string/Make.defs

CFLAGS+=-isystem $(TOPDIR)/include
#CFLAGS+=-Iarch/$(CONFIG_ARCH)/include
#CFLAGS+=-Iarch/$(CONFIG_ARCH)/$(CONFIG_ARCH_CHIP_FAMILY)

install: $(OBJS)
	$(AR) rcs $(TOPDIR)/libc.a $(OBJS)

clean:
	$(RM) -rf $(OBJS) $(DEPDIR)

include $(TOPDIR)/tools/Depends.mk


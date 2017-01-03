-include $(TOPDIR)/.config
include $(TOPDIR)/tools/Dequote.mk
-include $(TOPDIR)/Make.defs

CSRCS:=
include stdio/Make.defs
include string/Make.defs

#sysincludes must be last system include dir.
SYSINCLUDES=$(shell $(CC) --print-file-name=include)
#CFLAGS+=-Iarch/$(CONFIG_ARCH)/include
#CFLAGS+=-Iarch/$(CONFIG_ARCH)/$(CONFIG_ARCH_CHIP_FAMILY)
CFLAGS+=-isystem $(TOPDIR)/include -isystem$(SYSINCLUDES)

install: $(OBJS)
	$(AR) rcs $(TOPDIR)/libc.a $(OBJS)

clean:
	$(RM) -rf $(OBJS) $(DEPDIR)

include $(TOPDIR)/tools/Depends.mk


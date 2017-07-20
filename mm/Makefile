-include $(TOPDIR)/.config
include $(TOPDIR)/tools/Dequote.mk
include $(TOPDIR)/arch/$(CONFIG_ARCH)/Arch.defs
-include $(TOPDIR)/Make.defs

CSRCS:=heap_init.c heap_alloc.c

#sysincludes must be last system include dir.
SYSINCLUDES=$(shell $(CC) --print-file-name=include)
#CFLAGS+=-Iarch/$(CONFIG_ARCH)/include
#CFLAGS+=-Iarch/$(CONFIG_ARCH)/$(CONFIG_ARCH_CHIP_FAMILY)
CFLAGS+=-isystem $(TOPDIR)/include -isystem$(SYSINCLUDES)

install: $(OBJS)
	$(AR) rcs $(TOPDIR)/libmm.a $(OBJS)

clean:
	$(RM) -rf $(OBJS) $(DEPDIR)

include $(TOPDIR)/tools/Depends.mk


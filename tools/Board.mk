include $(TOPDIR)/.config
include $(TOPDIR)/tools/Dequote.mk
include $(TOPDIR)/arch/$(CONFIG_ARCH)/Arch.defs

#sysincludes must be last system include dir.
SYSINCLUDES=$(shell $(CC) --print-file-name=include)
CFLAGS+=-I../include
CFLAGS+=-I$(TOPDIR)/arch/$(CONFIG_ARCH)/include
CFLAGS+=-I$(TOPDIR)/arch/$(CONFIG_ARCH)/$(CONFIG_ARCH_CHIP_FAMILY)
CFLAGS+=-isystem $(TOPDIR)/include -isystem$(SYSINCLUDES)

install: $(OBJS) $(MAINOBJ) 
	$(AR) rcs $(TOPDIR)/libboard.a $(OBJS)

clean:
	$(RM) -rf $(OBJS) $(DEPDIR)

include $(TOPDIR)/tools/Depends.mk


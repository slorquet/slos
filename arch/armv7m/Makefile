#arch/armv7m/Makefile

-include $(TOPDIR)/.config
include $(TOPDIR)/tools/Dequote.mk
-include $(TOPDIR)/Make.defs
include $(CONFIG_ARCH_CHIP_FAMILY)/Make.defs

include Arch.defs
include $(CONFIG_ARCH_CHIP_FAMILY)/Chip.defs

VPATH += $(CONFIG_ARCH_CHIP_FAMILY)

CSRCS=$(CHIP_CSRCS)
CSRCS+=armv7m_nvic.c
MAINSRC=arch_start.c

MAINOBJ=$(MAINSRC:.c=.o)

#sysincludes must be last system include dir.
SYSINCLUDES=$(shell $(CC) --print-file-name=include)
CFLAGS+=-Iinclude -I$(CONFIG_ARCH_CHIP_FAMILY)
CFLAGS+=-isystem $(TOPDIR)/include -isystem$(SYSINCLUDES)

install: $(OBJS) $(MAINOBJ) 
	$(AR) rcs $(TOPDIR)/libarch.a $(OBJS)

clean:
	$(RM) -rf $(OBJS) $(MAINOBJ) $(DEPDIR)

include $(TOPDIR)/tools/Depends.mk

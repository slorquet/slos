#arch/armv8m/Makefile

-include $(TOPDIR)/.config
include $(TOPDIR)/tools/Dequote.mk
-include $(TOPDIR)/Make.defs
include Arch.defs
include $(CONFIG_ARCH_CHIP_FAMILY)/Make.defs

VPATH += $(CONFIG_ARCH_CHIP_FAMILY)

CSRCS=$(CHIP_CSRCS)
CSRCS+=armv8m_nvic.c

ifeq ($(CONFIG_ARMV7M_SYSTICK),y)
CSRCS+=armv8m_systick.c
endif

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

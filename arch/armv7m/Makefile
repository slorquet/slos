-include $(TOPDIR)/.config
CHIPDIR=$(patsubst "%",%,$(CONFIG_ARCH_CHIP_FAMILY))
-include $(TOPDIR)/Make.defs
include $(CHIPDIR)/Make.defs

include Arch.defs
include $(CHIPDIR)/Chip.defs

VPATH += $(CHIPDIR)

CSRCS=$(CHIP_CSRCS)
MAINSRC=arch_start.c

MAINOBJ=$(MAINSRC:.c=.o)

CFLAGS+=-I$(TOPDIR)/include -Iinclude -I$(CHIPDIR)

install: $(OBJS) $(MAINOBJ) 
	$(AR) rcs $(TOPDIR)/libs/libarch.a $(OBJS)

clean:
	$(RM) $(OBJS) $(MAINOBJ)


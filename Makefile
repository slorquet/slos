TOPDIR=$(shell pwd)

-include .config
include tools/Dequote.mk
-include Make.defs

BIN=slos

LDFLAGS= -T board/$(CONFIG_BOARD)/scripts/$(CONFIG_BOARD_LDSCRIPT)
LIBS=arch board

LDLIBS=$(addprefix -l, $(LIBS))

MAINOBJ=arch/$(CONFIG_ARCH)/arch_start.o

LIBGCC=$(shell $(CC) --print-libgcc-file-name)

default: $(BIN)

.PHONY: board/Kconfig

board/Kconfig:
	$(MAKE) -C board/ TOPDIR="$(TOPDIR)" Kconfig

menuconfig: board/Kconfig
	$(Q) kconfig-mconf Kconfig

$(foreach LIB, $(LIBS), $(eval $(call DIR_template,$(LIB),install)))

include/config.h: .config
	tools/mkconfig.sh .config $@

$(BIN): include/config.h $(foreach LIB, $(LIBS), $(LIB)_install)
	$(LD) --entry=arch_start $(LDFLAGS) -L. \
		-o $(BIN) $(MAINOBJ) --start-group $(LDLIBS) $(LIBGCC) --end-group
	@size -A $(BIN)

$(foreach LIB, $(LIBS), $(eval $(call DIR_template,$(LIB),clean)))

clean: $(foreach LIB, $(LIBS), $(LIB)_clean)
	$(RM) $(addsuffix .a, $(LIBS))

distclean: clean
	$(RM) board/Kconfig
	$(RM) .config


TOPDIR=$(shell pwd)

-include .config
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

$(BIN): $(foreach LIB, $(LIBS), $(LIB)_install)
	$(LD) --entry=arch_start $(LDFLAGS) -Llibs \
		-o $(BIN) $(MAINOBJ) --start-group $(LDLIBS) $(LIBGCC) --end-group

clean:
	$(MAKE) -C arch TOPDIR="$(TOPDIR)" clean
	$(RM) libs/*.a

distclean: clean
	$(RM) board/Kconfig
	$(RM) .config


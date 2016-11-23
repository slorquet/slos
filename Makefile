TOPDIR=$(shell pwd)

-include .config
-include Make.defs

BIN=slos

LDFLAGS=
LIBS=arch board

LDLIBS=$(addprefix -l, $(LIBS))

#MAINOBJ:=arch/$(CONFIG_ARCH)/entry.o

LIBGCC=$(shell $(CC) --print-libgcc-file-name)

default: $(BIN)

.PHONY: board/Kconfig

board/Kconfig:
	$(MAKE) -C board/ TOPDIR="$(TOPDIR)" Kconfig

menuconfig: board/Kconfig
	$(Q) kconfig-mconf Kconfig

$(foreach LIB, $(LIBS), $(eval $(call DIR_template,$(LIB),install)))

$(BIN): $(MAINOBJ) $(foreach LIB, $(LIBS), $(LIB)_install)
	$(LD) --entry=__start $(LDFLAGS) -Llib \
		-o $(BIN) $(MAINOBJ) --start-group $(LDLIBS) $(LIBGCC) --end-group

distclean:
	$(RM) libs/*.a
	$(RM) board/Kconfig
	$(RM) .config


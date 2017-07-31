TOPDIR=$(shell pwd)

-include .config
include tools/Dequote.mk
-include Make.defs

BIN=slos

LDFLAGS= -T board/$(CONFIG_BOARD)/scripts/$(CONFIG_BOARD_LDSCRIPT) -Map System.map

LIBS=arch board c mm
SUBDIRS=arch board libc mm

LDLIBS=$(addprefix -l, $(LIBS))

MAINOBJ=arch/$(CONFIG_ARCH)/arch_start.o


default: $(BIN)

.PHONY: board/Kconfig

board/Kconfig:
	$(MAKE) -C board/ TOPDIR="$(TOPDIR)" Kconfig

menuconfig: board/Kconfig
	$(Q) kconfig-mconf Kconfig

$(foreach SUBDIR, $(SUBDIRS), $(eval $(call DIR_template,$(SUBDIR),install)))

include/config.h: .config
	tools/mkconfig.sh .config $@

$(BIN): include/config.h $(foreach SUBDIR, $(SUBDIRS), $(SUBDIR)_install)
	$(LD) --entry=arch_start $(LDFLAGS) -L. \
		-o $(BIN) $(MAINOBJ) --start-group $(LDLIBS) $(LIBGCC) --end-group
	@size -A $(BIN)

$(foreach SUBDIR, $(SUBDIRS), $(eval $(call DIR_template,$(SUBDIR),clean)))

clean: $(foreach SUBDIR, $(SUBDIRS), $(SUBDIR)_clean)
	$(RM) $(addsuffix .a, $(addprefix lib, $(LIBS)))

distclean: clean
	$(RM) board/Kconfig
	$(RM) .config
	$(RM) $(BIN)


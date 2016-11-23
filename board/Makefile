-include $(TOPDIR)/.config
-include $(TOPDIR)/Make.defs

BOARDDIR=$(patsubst "%",%,$(CONFIG_BOARD_DIR))

.PHONY: Kconfig

install:
	$(MAKE) -C $(BOARDDIR)/src TOPDIR="$(TOPDIR)" install

clean:
	$(MAKE) -C $(BOARDDIR)/src TOPDIR="$(TOPDIR)" clean

Kconfig:
	$(TOPDIR)/tools/mk-board-kconfig.sh


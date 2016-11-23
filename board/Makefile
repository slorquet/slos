-include $(TOPDIR)/.config
-include $(TOPDIR)/Make.defs

.PHONY: Kconfig

install:
	touch $(TOPDIR)/libs/libboard.a

Kconfig:
	$(TOPDIR)/tools/mk-board-kconfig.sh


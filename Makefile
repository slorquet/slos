TOPDIR=$(shell pwd)

-include .config

.PHONY: board/Kconfig
board/Kconfig:
	cd board && TOPDIR=$(TOPDIR) $(MAKE) Kconfig

menuconfig: board/Kconfig
	$(Q) kconfig-mconf Kconfig

slos:
	cd arch/$(CONFIG_ARCH)/ && $(MAKE) $(BIN)

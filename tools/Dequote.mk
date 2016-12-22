#the string values in the .config files are quotes
#however make variables do not need this.
#this script removes the string quotes on selected vars
CONFIG_ARCH_CHIP_FAMILY:=$(patsubst "%",%,$(CONFIG_ARCH_CHIP_FAMILY))
CONFIG_ARCH:=$(patsubst "%",%,$(CONFIG_ARCH))
CONFIG_BOARD:=$(patsubst "%",%,$(CONFIG_BOARD))
CONFIG_BOARD_LDSCRIPT:=$(patsubst "%",%,$(CONFIG_BOARD_LDSCRIPT))

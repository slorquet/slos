#!/bin/sh
openocd \
	-f interface/ftdi/jtag-lock-pick_tiny_2.cfg \
	-c "ftdi_serial FTWQEJ2A" \
	-c "transport select swd" \
	-f target/stm32f1x.cfg \
	-c "reset_config none"


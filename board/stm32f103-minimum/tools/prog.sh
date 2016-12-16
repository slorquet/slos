#!/bin/sh
openocd $@ \
	-f interface/ftdi/jtag-lock-pick_tiny_2.cfg \
	-c "transport select swd" \
	-f target/stm32f1x.cfg \
	-c "reset_config srst_only connect_assert_srst" \
	-c "program slos verify reset exit"


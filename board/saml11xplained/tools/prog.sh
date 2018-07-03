#!/bin/sh
openocd $@ \
	-f board/st_nucleo_l476rg.cfg \
	-c "program slos verify reset exit"


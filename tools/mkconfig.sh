#!/bin/sh
#makes config.h from .config
if [ $# -ne 2 ]; then
  echo "arguments required"
  exit 1
fi
if [ ! -r $1 ]; then
  echo "config file not found"
  exit 1
fi
CONFIG=$1
OUTPUT=$2
echo '/* config.h generated from .config, do not edit */' > $OUTPUT
echo '#ifndef __CONFIG__H__' >> $OUTPUT
echo '#define __CONFIG__H__' >> $OUTPUT
echo '' >> $OUTPUT

awk '/^CONFIG_/ { split($0,a,"="); printf("#define %s %s\n", a[1], a[2]); }' .config >> $OUTPUT

echo '' >> $OUTPUT
echo '#endif /* __CONFIG__H__ */' >> $OUTPUT


This folder is for armv8/cortexm23

Toolchain must be recent enough to support -march=armv8-m. Example:
https://developer.arm.com/open-source/gnu-toolchain/gnu-rm/downloads

If the cpu has no secure extension or is built in single mode (only secure or
non secure), then it boots like a cortex m4

Ifthe cpu has the secure extension and is booting in secure mode, the user is
responsible for starting the non-secure code.

If the project has BOTH secure and non secure modes, then a two-pass build is
required.


#!/bin/bash

export ARCH=arm64

export PATH=$PATH:/home/user/kernel/gcc/bin
export CROSS_COMPILE=aarch64-linux-android-

export PATH=$PATH:/home/user/kernel/10.3/bin
export CROSS_COMPILE=aarch64-none-linux-gnu-

mkdir ../out

make ARCH=arm64 O=../out merge_kirin970_defconfig
make ARCH=arm64 O=../out -j4

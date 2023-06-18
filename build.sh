#!/bin/bash

export ARCH=arm64

# 请自行修改交叉编译器路径及名称
export PATH=$PATH:/home/user/kernel/10.3/bin
export CROSS_COMPILE=aarch64-linux-android-

mkdir ../out

make ARCH=arm64 O=../out merge_kirin970_defconfig
make ARCH=arm64 O=../out -j$(($(nproc) * 2))

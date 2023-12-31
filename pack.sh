#!/bin/bash
mkdir ../build_out
cp -f ../out/arch/arm64/boot/Image.gz ./tools
BUILD_DATE=`date +%Y%m%d`
cd ./tools || exit
./mkbootimg --kernel Image.gz --base 0x0 --cmdline "loglevel=4 initcall_debug=n page_tracker=on unmovable_isolate1=2:192M,3:224M,4:256M printktimer=0xfff0a000,0x534,0x538 androidboot.selinux=permissive buildvariant=user" --tags_offset 0x07A00000 --kernel_offset 0x00080000 --ramdisk_offset 0x07C00000 --header_version 1 --os_version 9 --os_patch_level 2019-05-05  --output kernel-$BUILD_DATE-permissive.img
./mkbootimg --kernel Image.gz --base 0x0 --cmdline "loglevel=4 initcall_debug=n page_tracker=on unmovable_isolate1=2:192M,3:224M,4:256M printktimer=0xfff0a000,0x534,0x538 androidboot.selinux=enforcing buildvariant=user" --tags_offset 0x07A00000 --kernel_offset 0x00080000 --ramdisk_offset 0x07C00000 --header_version 1 --os_version 9 --os_patch_level 2019-05-05  --output kernel-$BUILD_DATE-enforcing.img
mv -f *.img ../../build_out
rm -f Image.gz
cd ../..
echo 完成！

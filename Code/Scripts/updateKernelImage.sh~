#!/bin/bash
echo Creating loop node of kernel Image
sudo losetup /dev/loop0 ../KernelImage/IIITBKernel.img
echo Mounting kernel Image
sudo mount /dev/loop0 /mnt
sudo cp ../Build/kernel /mnt/kernel
sudo umount /dev/loop0
sudo losetup -d /dev/loop0

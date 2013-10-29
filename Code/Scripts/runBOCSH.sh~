#!/bin/bash

echo Mounting Kernel image
sudo /sbin/losetup /dev/loop0 BootloaderImage/IIITBKernel.img
echo Starting BOCSH
sudo bochs -f ../BOCHS/bochsConfigFile
echo Unmounting the Kernel image..
sudo /sbin/losetup -d /dev/loop0

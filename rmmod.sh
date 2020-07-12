# /bin/bash

rmmod rmmod.ko
insmod rmmod.ko
rmmod getpidofile.ko
dmesg -C

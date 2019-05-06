#/bin/bash
sudo losetup --offset 1048576 -f ../../disk.img && sudo mount /dev/loop0 /mnt

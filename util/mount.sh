#/bin/bash
sudo losetup --offset 1048576 -f $1 && sudo mount /dev/loop0 /mnt

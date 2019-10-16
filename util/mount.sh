#/bin/bash
dev=$(losetup -f)
sudo losetup --offset 1048576 -f $1 && sudo mount $dev /mnt

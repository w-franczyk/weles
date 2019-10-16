#/bin/bash
dev=$(mount | grep /mnt | cut -d' ' -f1)
sudo umount /mnt && sudo losetup -d $dev

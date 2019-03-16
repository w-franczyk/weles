STAGE1_BINARY=$1
VIRTUAL_DISK=$2
STAGE1_MAX_SIZE=446
if [ $(stat -c%s $STAGE1_BINARY) -gt $STAGE1_MAX_SIZE ]
then
	echo "ERR: Stage1 binary too big. Exiting..."
	exit 2
fi

echo "INFO: flushing the old stage 1 code"
dd if=/dev/zero of=$VIRTUAL_DISK conv=notrunc bs=1 count=$STAGE1_MAX_SIZE 
echo "INFO: writing the new stage 1 code at MBR"
dd if=stage1.bin of=$VIRTUAL_DISK conv=notrunc

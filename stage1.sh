STAGE1_BINARY="stage1.bin"
echo -n "INFO: Building stage1.asm... "
nasm -Wall -O0 stage1.asm -o $STAGE1_BINARY -l $STAGE1_BINARY.lst
if [ $? = 0 ]
then
	echo "Okay."
else
	echo "Error, exiting..."
  exit 1
fi

STAGE1_MAX_SIZE=446
if [ $(stat -c%s $STAGE1_BINARY) -gt $STAGE1_MAX_SIZE ]
then
	echo "ERR: Stage1 binary too big. Exiting..."
	exit 2
fi

echo "INFO: flushing the old stage 1 code"
dd if=/dev/zero of=disk.img conv=notrunc bs=1 count=$STAGE1_MAX_SIZE 
echo "INFO: writing the new stage 1 code at MBR"
dd if=stage1.bin of=disk.img conv=notrunc

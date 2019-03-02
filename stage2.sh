STAGE2_BINARY="stage2.bin"
echo -n "INFO: Building $STAGE2_BINARY... "
nasm -Wall -g stage2.asm -o $STAGE2_BINARY -l $STAGE2_BINARY.lst 
if [ $? = 0 ]
then
	echo "Okay."
else
	echo "Error, exiting..."
  exit 1
fi

SECTOR_SIZE=512
FIRST_SECTOR=1
LAST_SECTOR=2047
let SECTOR_COUNT=$LAST_SECTOR-$FIRST_SECTOR
let STAGE2_MAX_SIZE=$SECTOR_COUNT*$SECTOR_SIZE
if [ $(stat -c%s $STAGE2_BINARY) -gt $STAGE2_MAX_SIZE ]
then
	echo "ERR: Stage1 binary too big. Exiting..."
	exit 2
fi

echo "INFO: flushing the old stage 1 code"
dd if=/dev/zero of=disk.img conv=notrunc bs=$SECTOR_SIZE seek=$FIRST_SECTOR count=$SECTOR_COUNT
echo "INFO: writing the new stage 1 code at MBR"
dd if=$STAGE2_BINARY of=disk.img conv=notrunc bs=$SECTOR_SIZE seek=$FIRST_SECTOR

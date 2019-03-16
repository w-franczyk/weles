STAGE2_BINARY=$1
VIRTUAL_DISK=$2
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
dd if=/dev/zero of=$VIRTUAL_DISK conv=notrunc bs=$SECTOR_SIZE seek=$FIRST_SECTOR count=$SECTOR_COUNT
echo "INFO: writing the new stage 1 code at MBR"
dd if=$STAGE2_BINARY of=$VIRTUAL_DISK conv=notrunc bs=$SECTOR_SIZE seek=$FIRST_SECTOR

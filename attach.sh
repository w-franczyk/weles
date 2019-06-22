if [ -z "$TOOL" ]; then
  TOOL=cgdb
fi

$TOOL -ex "file bin/kernel.bin" -ex "target remote localhost:1234"

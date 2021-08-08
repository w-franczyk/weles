# Weles OS
Very simple operating system with a custom bootloader and set of basic functions:
- FAT filesystem & disk I/O
- VGA text ouput
- PS/2 keyboard input (stdin like).

Available through the built-in commands:
```
pwd, cd, ls, write, cat, rm
```
or through the C interface:
```
void sysPutchar(char c);
void sysFileDelete(const char* path);
int sysFileRead(const char* path, char* outBuf, unsigned maxSize);
int sysFileWrite(const char* path, const char* buf, unsigned size);
void sysStdin(char* destination);
void sysGetDirContents(const char* path, char* outBuf, unsigned outBufSize);
int sysStat(const char* path);
```

The OS is obviously not very usable and it has been created for fun & learn. Feel free to copy and modify any piece of this code as well as experiment with developing your own tools for the Weles OS! ;)

## Compiling & running

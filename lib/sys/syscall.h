#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

void sysPutchar(char c);
int fileOpen(const char* path);
void fileClose(int fileDescriptor);
int fileRead(int fileDescriptor);
int fileWrite(int fileDescriptor);
void sysStdin(char* destination);

#ifdef __cplusplus
}; // extern "C"
#endif

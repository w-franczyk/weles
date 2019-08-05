#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

void sysPutchar(char c);
void sysFileDelete(const char* path);
int sysFileRead(const char* path, char* outBuf, unsigned maxSize);
int sysFileWrite(const char* path, const char* buf, unsigned size);
void sysStdin(char* destination);
void sysGetDirContents(const char* path, char* outBuf, unsigned outBufSize);
int sysStat(const char* path);

#ifdef __cplusplus
}; // extern "C"
#endif

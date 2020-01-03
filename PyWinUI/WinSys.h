#ifndef WINSYS_H
#define WINSYS_H

LONG WINAPI Local_UnhandledExceptionFilter(PEXCEPTION_POINTERS pExcept);
void DumpMiniDump(HANDLE hFile, PEXCEPTION_POINTERS excpInfo);

#endif 
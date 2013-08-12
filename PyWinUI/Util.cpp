
#include "stdafx.h"
#include <Windows.h>
#include <Shellapi.h>
#include <string>
#include "Util.h"
#include <atlenc.h>
#include <Tlhelp32.h>

#pragma comment(lib, "shell32.lib")

int                     g_exitcode;
int						g_isTimeOut;

BOOL DeleteFolder(LPCTSTR pDirPath) 
{ 
	TCHAR DeleteDir[MAX_PATH+1] = {0};
	StringCchCopy( DeleteDir, MAX_PATH, pDirPath );

	SHFILEOPSTRUCT FileOp; 
	ZeroMemory((void*)&FileOp,sizeof(SHFILEOPSTRUCT));

	FileOp.fFlags = FOF_NOCONFIRMATION; 
	FileOp.hNameMappings = NULL; 
	FileOp.hwnd = NULL; 
	FileOp.lpszProgressTitle = NULL; 
	FileOp.pFrom = DeleteDir; 
	FileOp.pTo = NULL; 
	FileOp.wFunc = FO_DELETE; 

	return (SHFileOperation(&FileOp) == 0);
}

void LOGEx1(LPCTSTR lpszFormat, ...)
{
	va_list args;
	va_start(args, lpszFormat);

	HRESULT hr;
	TCHAR szBuffer[5120]={0};	
	hr = StringCchVPrintf(szBuffer, _countof(szBuffer), lpszFormat, args);
	szBuffer[ _countof(szBuffer) - 1 ] = 0;
	va_end(args);

	static int nIndex = 0;
	nIndex++;
	SYSTEMTIME sysToday;
	GetLocalTime(&sysToday);
	CString strTime;
	strTime.Format( _T("%04d-%02d-%02d %02d:%02d:%02d:%04d_%d process %d")
		, sysToday.wYear
		, sysToday.wMonth
		, sysToday.wDay
		, sysToday.wHour
		, sysToday.wMinute
		, sysToday.wSecond
		, sysToday.wMilliseconds
		, nIndex
		, GetCurrentProcessId());

	WritePrivateProfileString(_T("main"),strTime, szBuffer, GetExeFolderFilePath("applog.ini"));
}

void LOGA(LPCSTR msg)
{
	LOGEx(msg);
}

void LOGEx(CString msg)
{
	LOGEx1("%s", msg.GetBuffer());
	msg.ReleaseBuffer();
}

CString ExtractFileName(CString fullPath)
{
	int Where;
	Where=fullPath.ReverseFind('\\');
	if(Where==-1)
	{
		Where=fullPath.ReverseFind('/');
	}
	CString FileTitle=fullPath.Right(fullPath.GetLength()-1-Where);
	return FileTitle;
}
#pragma once 

#include <shellapi.h>
#include <shlobj.h>

CString GetBufferMD5String(BYTE* pBuf, DWORD dwBufLen);
CString GetStringMD5(CString strSrc);
LARGE_INTEGER GetFileSize(CString filePath);
BOOL GetEazDriver(TCHAR *chDriver);
BOOL DeleteFolder(LPCTSTR pDirPath);
void LOGEx1(LPCTSTR lpszFormat, ...);
void LOGEx(CString msg);
void LOGA(LPCSTR msg);
BOOL DES_CBC_Encode(BYTE* pbKey, DWORD dwKeyLen, BYTE* pbIV, DWORD dwIVLen, BYTE* pInBuf, DWORD dwInBufLen, BYTE** ppOutBuf, DWORD* pdwOutLen);
BOOL DES_CBC_Decode(BYTE* pbKey, DWORD dwKeyLen, BYTE* pbIV, DWORD dwIVLen, BYTE* pInBuf, DWORD dwInBufLen, BYTE** ppOutBuf, DWORD* pdwOutLen);
CString DesEncryptString(CString strPlain);
CString DesDeccryptString(CString strCipher);
CString MyBase64Encode(CString strSrc);
CStringA Base64EncodeBuf(BYTE* pBuf, DWORD dwLen);
void Base64Decode(CString& strContent);
CStringA Base64Decode(CStringA strAContent);
BOOL Base64DecodeBuf(CStringA strSrc, BYTE** ppDecodeBuf,  DWORD& dwOutBuf);
CString GetFileMd5(CString filePath);
CString ExecuteDosCommand(CString csExeName, CString csArguments, BOOL bWait, DWORD dwMilliseconds);
BOOL IsProcessRunning(LPCTSTR pszProcName);
BOOL IsXunleiRunning();
CStringA HexEncodeBuf(BYTE* pBuf, DWORD dwLen);
CString ExtractFileName(CString fullPath);

__declspec(selectany) TCHAR g_szExePath[MAX_PATH + 1] = {0};
inline LPCTSTR GetExePath()
{
	if (!g_szExePath[0])
		::GetModuleFileName(NULL, g_szExePath, MAX_PATH);

	return g_szExePath;
}

__declspec(selectany) TCHAR g_szExeFolder[MAX_PATH + 1] = {0};
inline LPCTSTR GetExeFolder()
{
	if (!g_szExeFolder[0])
	{
		memcpy(g_szExeFolder, GetExePath(), MAX_PATH);
		::PathRemoveFileSpec(g_szExeFolder);
	}
	return g_szExeFolder;
}

__declspec(selectany) TCHAR g_szBuffer[MAX_PATH + 1] = {0};
inline LPCTSTR GetExeFolderFilePath(LPCTSTR pMore, TCHAR *szBuffer = g_szBuffer)
{
	// 注意用默认参数的时候有潜在的多线程问题
	::PathCombine(szBuffer, GetExeFolder(), pMore);
	return szBuffer;
}

__declspec(selectany) TCHAR g_szAppDataPath[MAX_PATH + 1] = {0};
inline LPCTSTR GetAppDataPath()
{
	if (!g_szAppDataPath[0])
	{
		TCHAR szFolder[MAX_PATH] = { 0 };
		::SHGetSpecialFolderPath( NULL, szFolder, CSIDL_APPDATA, TRUE );
		::PathCombine( g_szAppDataPath, szFolder, _T("360mobilemgr") );
		if ( !::PathFileExists( g_szAppDataPath ) )
			::CreateDirectory( g_szAppDataPath, NULL );
	}

	return g_szAppDataPath;
}
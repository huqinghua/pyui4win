// DbgHelper.cpp: implementation of the CDbgHelper class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "MDbgHelper.h"
#include "shlwapi.h"
#pragma  comment (lib, "shlwapi")
#pragma comment(lib, "version")
#include <strsafe.h>
#include "Util.h"

//////////////////////////////////////////////////////////////////////


PFN_UnhandledExceptionFilter	CMDbgHelper::_PreExceptionFilter = NULL ;
PFN_MiniDumpWriteDump			CMDbgHelper::_MiniDumpWriteDump	= NULL ;

// Patch for SetUnhandledExceptionFilter 
const BYTE c_PatchBytes[5] = { 0x33, 0xC0, 0xC2, 0x04, 0x00 };

// Original bytes at the beginning of SetUnhandledExceptionFilter 
BYTE OriginalBytes[5] = {0};

void InvokeUploader(LPCTSTR lpFileName);

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

LPCTSTR DEFAULT_CAPTION = _T("Oops");
LPCTSTR DEFAULT_CONTENT = _T("There is an exception occured.");

CString GetAppTitle()
{
	TCHAR buffer[MAX_PATH] = {0};
	GetModuleFileName(GetModuleHandle(0), buffer, MAX_PATH);
	CString str = PathFindFileName(buffer);
	int nIndex = str.Find(_T("."));
	if (nIndex != -1)
		str = str.Mid(0, nIndex);
	return str;
}

CMDbgHelper::CMDbgHelper()
{
	ZeroMemory(m_szDumpFile,sizeof(m_szDumpFile));
	ZeroMemory(m_szFullDump, sizeof(m_szFullDump));

	GetModuleFileName(NULL, m_szDumpFile, ARRAYSIZEOF(m_szDumpFile));
	ExpandEnvironmentStrings(_T("%appdata%"),m_szFullDump , MAX_PATH);

	CString strVer = _T("1.0.0.1001");

	BYTE  VersionBuffer[8192] = {0};
	DWORD dwVerSize;
	DWORD dwHandle;

	TCHAR buffer[MAX_PATH] = {0};
	GetModuleFileName(GetModuleHandle(0), buffer, MAX_PATH);
	dwVerSize = GetFileVersionInfoSize(buffer, &dwHandle);
	if (dwVerSize == 0 || dwVerSize > (sizeof(VersionBuffer) - 1))
	{
		goto SKIP_QUERY;
		return;
	}

	if (GetFileVersionInfo(buffer, 0, dwVerSize, VersionBuffer) == FALSE)
	{
		goto SKIP_QUERY;
		return;
	}

	VS_FIXEDFILEINFO* pInfo;
	unsigned int nInfoLen;

	if (VerQueryValue(VersionBuffer, "\\", (void**)&pInfo, &nInfoLen))
		strVer.Format("%d.%d.%d.%d", HIWORD(pInfo->dwFileVersionMS), LOWORD(pInfo->dwFileVersionMS), HIWORD(pInfo->dwFileVersionLS), LOWORD(pInfo->dwFileVersionLS));

SKIP_QUERY:
	PathAppend(m_szDumpFile, _T("..\\"));

	SYSTEMTIME st;
	GetLocalTime(&st);

	CString strFileName;
	strFileName.Format(_T("%s_dump_%s_%02d%02d%02d%02d%02d.dmp"), "NetWin", strVer, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);

	PathAppend(m_szDumpFile, strFileName);

	PathAppend(m_szFullDump,_T("NetWin\\FullDump.dmp"));

	m_dwDumpType = MiniDumpNormal;
	m_hDbgHelp = LoadLibrary(_T("dbghelp.dll"));
	_MiniDumpWriteDump = NULL;
	if( m_hDbgHelp ){
		*(FARPROC*)&_MiniDumpWriteDump = GetProcAddress(m_hDbgHelp,"MiniDumpWriteDump");
	}

	StringCchCopy( m_szCaption, _countof(m_szCaption), DEFAULT_CAPTION );
	StringCchCopy( m_szContent, _countof(m_szContent), DEFAULT_CONTENT );
}

CMDbgHelper::~CMDbgHelper()
{
	if( m_hDbgHelp )
	{
		FreeLibrary(m_hDbgHelp);
		m_hDbgHelp = NULL;
	}
}

HRESULT CMDbgHelper::SetFilter(DWORD dwDumpType)
{
	if( _MiniDumpWriteDump == NULL )
	{
		return E_FAIL;
	}

	_PreExceptionFilter = SetUnhandledExceptionFilter( _MiniDumpHanlder );
	bool bRet = EnforceFilter(true);
	m_dwDumpType = dwDumpType;

	return bRet ? S_OK : E_FAIL;
}

LONG WINAPI CMDbgHelper::_MiniDumpHanlder(PEXCEPTION_POINTERS pep)
{
	BOOL bRet = FALSE;
	
	__try
	{
		bRet = CreateMiniDump( pep, Instance()->GetDumpFileName(TRUE),TRUE );
		bRet = CreateMiniDump( pep, Instance()->GetDumpFileName(FALSE),FALSE );
	}
	__except( EXCEPTION_EXECUTE_HANDLER )
	{
		bRet = FALSE;
	}

	ExitProcess( pep->ExceptionRecord->ExceptionCode );
	return bRet;
}

////////////////////////////////////////////////////////////////////////////////
// EnforceFilter function 
// 

bool CMDbgHelper::EnforceFilter( bool bEnforce )
{
	DWORD ErrCode = 0;
	
	// Obtain the address of SetUnhandledExceptionFilter 
	HMODULE hLib = GetModuleHandle( _T("kernel32.dll") );

	if( hLib == NULL )
	{
		ErrCode = GetLastError();
		_ASSERTE( !_T("GetModuleHandle(kernel32.dll) failed.") );
		return false;
	}

	BYTE* pTarget = (BYTE*)GetProcAddress( hLib, "SetUnhandledExceptionFilter" );

	if( pTarget == 0 )
	{
		ErrCode = GetLastError();
		_ASSERTE( !_T("GetProcAddress(SetUnhandledExceptionFilter) failed.") );
		return false;
	}

	if( IsBadReadPtr( pTarget, sizeof(OriginalBytes) ) )
	{
		_ASSERTE( !_T("Target is unreadable.") );
		return false;
	}


	if( bEnforce )
	{
		// Save the original contents of SetUnhandledExceptionFilter 
		memcpy( OriginalBytes, pTarget, sizeof(OriginalBytes) );

		// Patch SetUnhandledExceptionFilter 
		if( !WriteMemory( pTarget, c_PatchBytes, sizeof(c_PatchBytes) ) )
			return false;
	}
	else
	{
		// Restore the original behavior of SetUnhandledExceptionFilter 
		if( !WriteMemory( pTarget, OriginalBytes, sizeof(OriginalBytes) ) )
			return false;
	}

	// Success 
	return true;
}


////////////////////////////////////////////////////////////////////////////////
// WriteMemory function 
// 

bool CMDbgHelper::WriteMemory( BYTE* pTarget, const BYTE* pSource, DWORD Size )
{
	DWORD ErrCode = 0;


	// Check parameters 

	if( pTarget == 0 )
	{
		_ASSERTE( !_T("Target address is null.") );
		return false;
	}

	if( pSource == 0 )
	{
		_ASSERTE( !_T("Source address is null.") );
		return false;
	}

	if( Size == 0 )
	{
		_ASSERTE( !_T("Source size is null.") );
		return false;
	}

	if( IsBadReadPtr( pSource, Size ) )
	{
		_ASSERTE( !_T("Source is unreadable.") );
		return false;
	}


	// Modify protection attributes of the target memory page 

	DWORD OldProtect = 0;

	if( !VirtualProtect( pTarget, Size, PAGE_EXECUTE_READWRITE, &OldProtect ) )
	{
		ErrCode = GetLastError();
		_ASSERTE( !_T("VirtualProtect() failed.") );
		return false;
	}


	// Write memory 

	memcpy( pTarget, pSource, Size );


	// Restore memory protection attributes of the target memory page 

	DWORD Temp = 0;

	if( !VirtualProtect( pTarget, Size, OldProtect, &Temp ) )
	{
		ErrCode = GetLastError();
		_ASSERTE( !_T("VirtualProtect() failed.") );
		return false;
	}

	// Success 

	return true;

}

////////////////////////////////////////////////////////////////////////////////
// CreateMiniDump() function
//

BOOL CMDbgHelper::CreateMiniDump( EXCEPTION_POINTERS* pep ,LPCTSTR szMinDump ,BOOL bFull ) 
{
	// Open the file 
	// _T("MiniDump.dmp")
	if( _MiniDumpWriteDump == NULL )
		return FALSE;

	BOOL bRet = FALSE;
	HANDLE hFile = CreateFile( szMinDump , GENERIC_READ | GENERIC_WRITE, 
		0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL ); 
	
	if( ( hFile != NULL ) && ( hFile != INVALID_HANDLE_VALUE ) ) 
	{
		// Create the minidump
		
		MINIDUMP_EXCEPTION_INFORMATION mdei; 
		
		mdei.ThreadId           = GetCurrentThreadId(); 
		mdei.ExceptionPointers  = pep; 
		mdei.ClientPointers     = FALSE; 
		
		MINIDUMP_TYPE mdt;
		if( bFull)
			mdt = (MINIDUMP_TYPE)(MiniDumpWithFullMemory|MiniDumpWithHandleData); 
		else
			mdt = MiniDumpWithIndirectlyReferencedMemory;
		
		BOOL rv = _MiniDumpWriteDump( GetCurrentProcess(), GetCurrentProcessId(), 
			hFile, mdt, (pep != 0) ? &mdei : 0, 0, 0 ); 
		
		if( rv ) 		
		{
			bRet = TRUE;
		}
		
		CloseHandle( hFile ); 		
	}

	return bRet;
}


void CMDbgHelper::SetDumpFile(LPCTSTR pszDumpFile)
{
	if( !pszDumpFile || _tcslen(pszDumpFile) > MAX_PATH - 1 )
		return;

	StringCchCopy(m_szDumpFile, _countof(m_szDumpFile), pszDumpFile );
}

LPCTSTR CMDbgHelper::GetDumpFileName(BOOL bFull)
{
	if( bFull)
		return m_szFullDump;

	return m_szDumpFile;
}

void CMDbgHelper::SetPromptInfo(LPCTSTR lpszCaption, LPCTSTR lpszContent)
{
	_ASSERTE( lpszCaption != NULL && lpszContent != NULL );
	if( lpszCaption )
		StringCchCopy( m_szCaption, _countof(m_szCaption), lpszCaption );
	if( lpszContent )
		StringCchCopy( m_szContent, _countof(m_szContent), lpszContent );
}

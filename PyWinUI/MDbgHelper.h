// DbgHelper.h: interface for the CDbgHelper class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DBGHELPER_H__5BE6B225_D08A_44EF_A68C_1BA41E52D2D3__INCLUDED_)
#define AFX_DBGHELPER_H__5BE6B225_D08A_44EF_A68C_1BA41E52D2D3__INCLUDED_

#include <windows.h>
#include <tchar.h>
#include <dbghelp.h>
#include <stdio.h>

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////////


#ifndef _countof
#define _countof(_Array) (sizeof(_Array) / sizeof(_Array[0]))
#endif

#ifndef MiniDumpWithThreadInfo
#define MiniDumpWithThreadInfo	0x00001000
#endif

typedef LONG (WINAPI *PFN_UnhandledExceptionFilter)( struct _EXCEPTION_POINTERS* ExceptionInfo );
typedef BOOL (WINAPI *PFN_MiniDumpWriteDump)(
								  IN HANDLE hProcess,
								  IN DWORD ProcessId,
								  IN HANDLE hFile,
								  IN MINIDUMP_TYPE DumpType,
								  IN CONST PMINIDUMP_EXCEPTION_INFORMATION ExceptionParam, OPTIONAL
								  IN CONST PMINIDUMP_USER_STREAM_INFORMATION UserStreamParam, OPTIONAL
								  IN CONST PMINIDUMP_CALLBACK_INFORMATION CallbackParam OPTIONAL
								  );

#define ARRAYSIZEOF(x) (sizeof(x)/sizeof(x[0]))

class CMDbgHelper  
{
	CMDbgHelper();

public:	
	void SetPromptInfo( LPCTSTR lpszCaption, LPCTSTR lpszContent );
	LPCTSTR GetDumpFileName(BOOL bFull);
	void SetDumpFile( LPCTSTR pszDumpFile );
	HRESULT SetFilter( DWORD dwDumpType = MiniDumpNormal);
	static CMDbgHelper* Instance() { static CMDbgHelper s_Instance;  return &s_Instance; }	
	virtual ~CMDbgHelper();

protected:
	// EnforceFilter function 
	// 
	// If bEnforce is "true", the function overwrites the beginning of 
	// SetUnhandledExceptionFilter function with a patch which rejects  
	// all subsequent attempts to register a filter.
	// If bEnforce is "false", the original functionality of 
	// SetUnhandledExceptionFilter is restored. 
	// 
	static bool EnforceFilter( bool bEnforce );	
	// WriteMemory function 
	// 
	// This function writes the specified sequence of bytes from 
	// the source memory into the target memory. In addition, the function 
	// modifies virtual memory protection attributes of the target memory page 
	// to make sure that it is writeable.
	// 
	static bool WriteMemory( BYTE* pTarget, const BYTE* pSource, DWORD Size );
	static BOOL CreateMiniDump( EXCEPTION_POINTERS* pep ,LPCTSTR szMinDump ,BOOL bFull );
	static LONG WINAPI _MiniDumpHanlder(PEXCEPTION_POINTERS pep );
protected:

	static PFN_UnhandledExceptionFilter	_PreExceptionFilter;
	static PFN_MiniDumpWriteDump		_MiniDumpWriteDump;
	TCHAR  m_szDumpFile[MAX_PATH];
	TCHAR m_szFullDump[MAX_PATH];
	TCHAR  m_szCaption[MAX_PATH];
	TCHAR  m_szContent[1024];
	DWORD  m_dwDumpType;
	HMODULE m_hDbgHelp;
	
	
};

#endif // !defined(AFX_DBGHELPER_H__5BE6B225_D08A_44EF_A68C_1BA41E52D2D3__INCLUDED_)

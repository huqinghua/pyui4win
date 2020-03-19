#include "stdafx.h"
#include <exdisp.h>
#include <comdef.h>
#include <string>
#include <shellapi.h>
#include <shlobj.h>
#include <Commdlg.h>
#include "Win32Api.h"
#include "Wininet.h"
#include "urlmon.h"

#pragma comment( lib, "wininet.lib" )
#pragma comment( lib, "urlmon.lib" )

extern HMODULE g_hModule;

CWin32Api::CWin32Api(void)
{
}

CWin32Api::~CWin32Api(void)
{
}

void CWin32Api::SetCurrentDirectoryToExePath()
{
	char szExeFolder[MAX_PATH + 1] = {0};
	::GetModuleFileName(NULL, szExeFolder, MAX_PATH);
	::PathRemoveFileSpec(szExeFolder);
	SetCurrentDirectory(szExeFolder);
}

void CWin32Api::Sleep(int nMillseconds)
{
	::Sleep(nMillseconds);
}

int CWin32Api::SetTimer(int hWnd, int nIDEvent, int uElapse)
{
	return ::SetTimer((HWND)hWnd, nIDEvent, uElapse, NULL);
}

int CWin32Api::KillTimer(int hWnd, int nIDEvent)
{
	return ::KillTimer((HWND)hWnd, nIDEvent);
}

int CWin32Api::SendMessageA(int hWnd, int Msg, int wParam, int lParam)
{
	return ::SendMessageA((HWND)hWnd, Msg, wParam, lParam);
}

int CWin32Api::PostMessageA(int hWnd, int Msg, int wParam, int lParam)
{
	return ::PostMessageA((HWND)hWnd, Msg, wParam, lParam);
}

void CWin32Api::MoveWindowRelative(int hWnd, int x, int y)
{
	RECT rcDlg = { 0 };
    ::GetWindowRect((HWND)hWnd, &rcDlg);
	::MoveWindow((HWND)hWnd, rcDlg.left+x, rcDlg.top+y, rcDlg.right - rcDlg.left, rcDlg.bottom - rcDlg.top, TRUE);
}
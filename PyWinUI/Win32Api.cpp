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


CWin32Api::CWin32Api(void)
{
}

CWin32Api::~CWin32Api(void)
{
}

std::string CWin32Api::GetExeDirectory()
{
	char szExeFolder[MAX_PATH + 1] = {0};
	::GetModuleFileName(NULL, szExeFolder, MAX_PATH);
	::PathRemoveFileSpec(szExeFolder);

	return szExeFolder;
}

void CWin32Api::SetCurrentDirectory(std::string dir)
{
	::SetCurrentDirectory(dir.c_str());
}

void CWin32Api::SetCurrentDirectoryToExePath()
{
	char szExeFolder[MAX_PATH + 1] = {0};
	::GetModuleFileName(NULL, szExeFolder, MAX_PATH);
	::PathRemoveFileSpec(szExeFolder);
	SetCurrentDirectory(szExeFolder);
}

void CWin32Api::SetWaitCursor()
{
	SetCursor(LoadCursor(NULL, IDC_WAIT));
}

void CWin32Api::SetArrowCursor()
{
	SetCursor(LoadCursor(NULL, IDC_ARROW));
}

void CWin32Api::ShellExcute(int hwnd,
							std::string lpOperation,
							std::string lpFile,
							std::string lpParameters,
							std::string lpDirectory,
							int nShowCmd
)
{
	::ShellExecute((HWND)hwnd,
		lpOperation.c_str(),
		lpFile.c_str(),
		lpParameters.c_str(),
		lpDirectory.c_str(),
		nShowCmd
		);
}

std::string CWin32Api::SelectFile(int hwnd, std::string filter)
{
	TCHAR szBuffer[MAX_PATH] = {0}; 
	OPENFILENAME ofn= {0}; 
	ofn.lStructSize = sizeof(ofn); 
	ofn.hwndOwner = (HWND)hwnd; 
	ofn.lpstrFilter = filter.c_str();
	ofn.lpstrInitialDir = NULL; 
	ofn.lpstrFile = szBuffer;
	ofn.nMaxFile = sizeof(szBuffer)/sizeof(szBuffer[0]); 
	ofn.nFilterIndex = 0; 
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_EXPLORER ;//标志如果是多选要加上OFN_ALLOWMULTISELECT
	BOOL bSel = GetOpenFileName(&ofn); 

	if(bSel)
	{
		return szBuffer;
	}
	else
		return "";
}

int CWin32Api::MessageBox(int hwnd, std::string text, std::string caption, int btntype)
{
	return ::MessageBoxA((HWND)hwnd, text.c_str(), caption.c_str(), btntype);
}

static int CALLBACK BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{
	if(uMsg==BFFM_SELCHANGED||uMsg==BFFM_INITIALIZED)
	{
		if(uMsg==BFFM_INITIALIZED)
		{
			::SendMessage(hwnd,BFFM_SETSELECTION,TRUE, LPARAM(lpData));
		}
	}
	return 0;
} 

std::string CWin32Api::SelectFolder(int hwnd, std::string title, std::string saveTag)
{
	TCHAR szBuffer[MAX_PATH] = {0};
	if (saveTag.length() > 0)
	{
		GetPrivateProfileString(_T("main"), saveTag.c_str(), _T(""), szBuffer, 
			MAX_PATH,GetExeFolderFilePath(_T("solution_path.ini")));
	}

	TCHAR szPath[MAX_PATH] = {0};
	BROWSEINFO br;
	ITEMIDLIST * pItem;
	br.hwndOwner = (HWND)hwnd; 
	br.iImage = 0;
	br.pszDisplayName = 0;
	br.lParam = (LPARAM)szBuffer ;
	br.lpfn = BrowseCallbackProc ;
	br.lpszTitle = title.c_str();
	br.pidlRoot = 0 ;
	br.ulFlags = BIF_RETURNONLYFSDIRS;
	pItem = SHBrowseForFolder(&br);
	if ( !SHGetPathFromIDList(pItem,szPath))
		return "";

	if (saveTag.length() > 0)
		WritePrivateProfileString(_T("main"),saveTag.c_str(), szPath, GetExeFolderFilePath(_T("solution_path.ini")));

	return szPath;
}

bool CWin32Api::CreateDirectory(std::string dir)
{
	return ::CreateDirectory(dir.c_str(), NULL);
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

BOOL CWin32Api::SetConnectionOptions(LPTSTR proxy_full_addr)
{
/*
	//conn_name: active connection name. 
	//proxy_full_addr : eg "210.78.22.87:8000"
	INTERNET_PER_CONN_OPTION_LIST list;
	BOOL    bReturn;
	DWORD   dwBufSize = sizeof(list);
	// Fill out list struct.
	list.dwSize = sizeof(list);
	// NULL == LAN, otherwise connectoid name.
	list.pszConnection = conn_name;
	// Set three options.
	list.dwOptionCount = 3;
	list.pOptions = new INTERNET_PER_CONN_OPTION[3];
	// Make sure the memory was allocated.
	if(NULL == list.pOptions)
	{
		// Return FALSE if the memory wasn't allocated.
		return FALSE;
	}
	// Set flags.
	list.pOptions[0].dwOption = INTERNET_PER_CONN_FLAGS;
	list.pOptions[0].Value.dwValue = PROXY_TYPE_DIRECT |
		PROXY_TYPE_PROXY;

	// Set proxy name.
	list.pOptions[1].dwOption = INTERNET_PER_CONN_PROXY_SERVER;
	list.pOptions[1].Value.pszValue = proxy_full_addr;//"http://proxy:80";

	// Set proxy override.
	list.pOptions[2].dwOption = INTERNET_PER_CONN_PROXY_BYPASS;
	list.pOptions[2].Value.pszValue = "local";

	// Set the options on the connection.
	bReturn = InternetSetOption(NULL,
		INTERNET_OPTION_PER_CONNECTION_OPTION, &list, dwBufSize);

	// Free the allocated memory.
	delete [] list.pOptions;
	InternetSetOption(NULL, INTERNET_OPTION_SETTINGS_CHANGED, NULL, 0);
	InternetSetOption(NULL, INTERNET_OPTION_REFRESH , NULL, 0);

	return bReturn;
*/
	INTERNET_PROXY_INFO struct_IPI;
	// Filling in structure
	struct_IPI.dwAccessType = INTERNET_OPEN_TYPE_PROXY;
	struct_IPI.lpszProxy = proxy_full_addr;
	struct_IPI.lpszProxyBypass = NULL;
	HRESULT hr = ::UrlMkSetSessionOption(INTERNET_OPTION_PROXY, (void *)&struct_IPI, sizeof(struct_IPI), 0); 
	return hr == S_OK;
}

BOOL CWin32Api::DisableConnectionProxy()
{
/*
	//conn_name: active connection name. 
	INTERNET_PER_CONN_OPTION_LIST list;
	BOOL    bReturn;
	DWORD   dwBufSize = sizeof(list);
	// Fill out list struct.
	list.dwSize = sizeof(list);
	// NULL == LAN, otherwise connectoid name.
	list.pszConnection = conn_name;
	// Set three options.
	list.dwOptionCount = 1;
	list.pOptions = new INTERNET_PER_CONN_OPTION[list.dwOptionCount];
	// Make sure the memory was allocated.
	if(NULL == list.pOptions)
	{
		// Return FALSE if the memory wasn't allocated.
		return FALSE;
	}
	// Set flags.
	list.pOptions[0].dwOption = INTERNET_PER_CONN_FLAGS;
	list.pOptions[0].Value.dwValue = PROXY_TYPE_DIRECT  ;
	// Set the options on the connection.
	bReturn = InternetSetOption(NULL,
		INTERNET_OPTION_PER_CONNECTION_OPTION, &list, dwBufSize);
	// Free the allocated memory.
	delete [] list.pOptions;
	InternetSetOption(NULL, INTERNET_OPTION_SETTINGS_CHANGED, NULL, 0);
	InternetSetOption(NULL, INTERNET_OPTION_REFRESH , NULL, 0);
	return bReturn;
*/

	INTERNET_PROXY_INFO struct_IPI;
	// Filling in structure
	struct_IPI.dwAccessType = INTERNET_OPEN_TYPE_DIRECT;
	struct_IPI.lpszProxy = NULL;
	struct_IPI.lpszProxyBypass = NULL;
	HRESULT hr = ::UrlMkSetSessionOption(INTERNET_OPTION_PROXY, (void *)&struct_IPI, sizeof(struct_IPI), 0); 
	return hr == S_OK;

}

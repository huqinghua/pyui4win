#include "stdafx.h"
#include <exdisp.h>
#include <comdef.h>
#include <string>
#include <shellapi.h>
#include <shlobj.h>
#include <Commdlg.h>
#include "Win32Api.h"

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

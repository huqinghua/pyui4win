#pragma once

class CWin32Api
{
public:
	CWin32Api(void);
	~CWin32Api(void);
	std::string GetExeDirectory();
	std::string GetPyUI4WinDirectory();
	std::string Conver2string(int addr);
	void SetCurrentDirectory(std::string dir);
	bool CreateDirectory(std::string dir);
	void SetCurrentDirectoryToExePath();
	void SetWaitCursor();
	void Sleep(int nMillseconds);
	int SetTimer(int hWnd, int nIDEvent, int uElapse); 
	int KillTimer(int hWnd, int nIDEvent);
	void SetArrowCursor();
	void ShellExcute(int hwnd,
		std::string lpOperation,
		std::string lpFile,
		std::string lpParameters,
		std::string lpDirectory,
		int nShowCmd
		);
	std::string SelectFile(int hwnd, std::string filter);
	int MessageBox(int hwnd, std::string text, std::string caption, int btntype);
	std::string SelectFolder(int hwnd, std::string title, std::string saveTag);
	BOOL SetConnectionOptions(LPTSTR proxy_full_addr);
	BOOL DisableConnectionProxy();
	void OutputDebugMsg(std::string msg);
	int SendMessageA(int hWnd, int Msg, int wParam, int lParam);
	int PostMessageA(int hWnd, int Msg, int wParam, int lParam);
	void MoveWindowRelative(int hWnd, int x, int y);
};

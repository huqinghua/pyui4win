#pragma once

class CWin32Api
{
public:
	CWin32Api(void);
	~CWin32Api(void);
	void SetCurrentDirectoryToExePath();
	void Sleep(int nMillseconds);
	int SetTimer(int hWnd, int nIDEvent, int uElapse); 
	int KillTimer(int hWnd, int nIDEvent);
	int SendMessageA(int hWnd, int Msg, int wParam, int lParam);
	int PostMessageA(int hWnd, int Msg, int wParam, int lParam);
	void MoveWindowRelative(int hWnd, int x, int y);
};

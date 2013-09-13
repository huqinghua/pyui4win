#include "stdafx.h"
#include <windows.h>
#include <shellapi.h>

#include "resource.h"
#include "PyFrameUI.hpp"
#include "PyFrameCreator.hpp"
// control related message
#define DUI_MSGTYPE_MENU                   (_T("menu"))
#define DUI_MSGTYPE_LINK                   (_T("link"))

#define DUI_MSGTYPE_TIMER                  (_T("timer"))
#define DUI_MSGTYPE_CLICK                  (_T("click"))

#define DUI_MSGTYPE_RETURN                 (_T("return"))
#define DUI_MSGTYPE_SCROLL                 (_T("scroll"))

#define DUI_MSGTYPE_DROPDOWN               (_T("dropdown"))
#define DUI_MSGTYPE_SETFOCUS               (_T("setfocus"))

#define DUI_MSGTYPE_KILLFOCUS              (_T("killfocus"))
#define DUI_MSGTYPE_ITEMCLICK 		   	   (_T("itemclick"))
#define DUI_MSGTYPE_TABSELECT              (_T("tabselect"))

#define DUI_MSGTYPE_ITEMSELECT 		   	   (_T("itemselect"))
#define DUI_MSGTYPE_ITEMEXPAND             (_T("itemexpand"))
#define DUI_MSGTYPE_WINDOWINIT             (_T("windowinit"))
#define DUI_MSGTYPE_BUTTONDOWN 		   	   (_T("buttondown"))
#define DUI_MSGTYPE_MOUSEENTER			   (_T("mouseenter"))
#define DUI_MSGTYPE_MOUSELEAVE			   (_T("mouseleave"))

#define DUI_MSGTYPE_TEXTCHANGED            (_T("textchanged"))
#define DUI_MSGTYPE_HEADERCLICK            (_T("headerclick"))
#define DUI_MSGTYPE_ITEMDBCLICK            (_T("itemdbclick"))
#define DUI_MSGTYPE_SHOWACTIVEX            (_T("showactivex"))

#define DUI_MSGTYPE_ITEMCOLLAPSE           (_T("itemcollapse"))
#define DUI_MSGTYPE_ITEMACTIVATE           (_T("itemactivate"))
#define DUI_MSGTYPE_VALUECHANGED           (_T("valuechanged"))

#define DUI_MSGTYPE_SELECTCHANGED 		   (_T("selectchanged"))

const TCHAR* const kCloseButtonControlName = _T("closebtn");
const TCHAR* const kMinButtonControlName = _T("minbtn");
const TCHAR* const kMaxButtonControlName = _T("maxbtn");
const TCHAR* const kRestoreButtonControlName = _T("restorebtn");

PyFrameUI::PyFrameUI()
{
}

PyFrameUI::~PyFrameUI()
{
}

void PyFrameUI::SetPyBaseUI(PyUIBase* frame) 
{
	m_frame = frame;
}

LPCTSTR PyFrameUI::GetWindowClassName() const
{
	return m_frame->GetWindowClassName();
}

void PyFrameUI::OnFinalMessage(HWND hWnd)
{
	WindowImplBase::OnFinalMessage(hWnd);
	delete this;
}

CDuiString PyFrameUI::GetSkinFile()
{
	return m_frame->GetSkinFile();
}

CDuiString PyFrameUI::GetSkinFolder()
{
	return _T("skin\\");
}

CControlUI* PyFrameUI::FindControl(LPCSTR ControlName)
{
	CControlUI* pControl = static_cast<CControlUI*>(m_PaintManager.FindControl(ControlName));
	return pControl;
}

LRESULT PyFrameUI::OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	BOOL bZoomed = ::IsZoomed(m_hWnd);
	LRESULT lRes = CWindowWnd::HandleMessage(uMsg, wParam, lParam);
	if (::IsZoomed(m_hWnd) != bZoomed)
	{
		if (!bZoomed)
		{
			CControlUI* pControl = static_cast<CControlUI*>(m_PaintManager.FindControl(kMaxButtonControlName));
			if( pControl ) pControl->SetVisible(false);
			pControl = static_cast<CControlUI*>(m_PaintManager.FindControl(kRestoreButtonControlName));
			if( pControl ) pControl->SetVisible(true);
		}
		else 
		{
			CControlUI* pControl = static_cast<CControlUI*>(m_PaintManager.FindControl(kMaxButtonControlName));
			if( pControl ) pControl->SetVisible(true);
			pControl = static_cast<CControlUI*>(m_PaintManager.FindControl(kRestoreButtonControlName));
			if( pControl ) pControl->SetVisible(false);
		}
	}

	return 0;
}

LRESULT PyFrameUI::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return __super::HandleMessage(uMsg, wParam, lParam);
}

void PyFrameUI::OnTimer(TNotifyUI& msg)
{
	CString name = msg.pSender->GetName();
	m_frame->OnTimer((LPCSTR)name, msg.wParam, msg.lParam);
}

void PyFrameUI::OnExit(TNotifyUI& msg)
{
	CString name = msg.pSender->GetName();
	m_frame->OnExit((LPCSTR)name, msg.wParam, msg.lParam);
}

void PyFrameUI::InitWindow()
{
	m_frame->InitWindow();
}

void PyFrameUI::OnPrepare(TNotifyUI& msg)
{
	CString name = msg.pSender->GetName();
	m_frame->OnPrepare((LPCSTR)name, msg.wParam, msg.lParam);

	HICON hIcon = (HICON)::LoadImage(CPaintManagerUI::GetInstance(), MAKEINTRESOURCE(IDI_ICON_WINGIRL), IMAGE_ICON, ::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON), LR_DEFAULTCOLOR);
	ASSERT(hIcon);
	::SendMessage(m_hWnd, WM_SETICON, (WPARAM) TRUE, (LPARAM) hIcon);
	hIcon = (HICON)::LoadImage(CPaintManagerUI::GetInstance(), MAKEINTRESOURCE(IDI_ICON_WINGIRL), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), LR_DEFAULTCOLOR);
	ASSERT(hIcon);
	::SendMessage(m_hWnd, WM_SETICON, (WPARAM) FALSE, (LPARAM) hIcon);
}

void PyFrameUI::Notify(TNotifyUI& msg)
{
	if (_tcsicmp(msg.sType, DUI_MSGTYPE_WINDOWINIT) == 0)
	{
		OnPrepare(msg);
	}
	else if (_tcsicmp(msg.sType, DUI_MSGTYPE_TIMER) == 0)
	{
		return OnTimer(msg);
	}
	else
	{
		if (_tcsicmp(msg.sType, DUI_MSGTYPE_CLICK) == 0)
		{
			if (_tcsicmp(msg.pSender->GetName(), kCloseButtonControlName) == 0)
			{
				OnExit(msg);
				return;
			}
			else if (_tcsicmp(msg.pSender->GetName(), kMinButtonControlName) == 0)
			{
				SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0);
				return;
			}
			else if (_tcsicmp(msg.pSender->GetName(), kMaxButtonControlName) == 0)
			{
				SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE, 0);
				return;
			}
			else if (_tcsicmp(msg.pSender->GetName(), kRestoreButtonControlName) == 0)
			{
				SendMessage(WM_SYSCOMMAND, SC_RESTORE, 0);
				return;
			}
		}

		CString nameA = msg.pSender->GetName();
		CString typeA = msg.sType;
		return m_frame->OnNotify((LPCSTR)nameA, (LPCSTR)typeA, msg.wParam, msg.lParam);
	}
}

LRESULT PyFrameUI::HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (m_frame->HandleCustomMessage(uMsg, wParam, lParam))
		bHandled = TRUE;

	return 0;
}
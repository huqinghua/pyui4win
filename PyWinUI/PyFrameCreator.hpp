
#ifndef PYFRAME_HPP
#define PYFRAME_HPP

#include<boost/python.hpp>
#include "PyFrameUI.hpp"
#include "duilib-python.h"

using namespace boost::python;

class UIWebBrowserWrap
{
public:
	UIWebBrowserWrap(CControlUI* control) {m_webBrowser = static_cast<CWebBrowserUI*>(control);}
	~UIWebBrowserWrap() {}

	void NavigateUrl(LPCTSTR lpszUrl) {m_webBrowser->NavigateUrl(lpszUrl);}
	void Navigate2(LPCTSTR lpszUrl) {m_webBrowser->Navigate2(lpszUrl);}

	void Refresh() {m_webBrowser->Refresh();}
	void Refresh2(int Level) {m_webBrowser->Refresh2(Level); }
	void GoBack() {m_webBrowser->GoBack(); }
	void GoForward() {m_webBrowser->GoForward(); }
	void SetHomePage(LPCTSTR lpszUrl) { m_webBrowser->SetHomePage(lpszUrl); }
	LPCTSTR GetHomePage() { return m_webBrowser->GetHomePage(); }
	void NavigateHomePage() { return m_webBrowser->NavigateHomePage(); }
	bool DoCreateControl(){ return m_webBrowser->DoCreateControl(); }
private:
	CWebBrowserUI* m_webBrowser;
};

class PyUIFactory
{
public:
	PyUIFactory() {}
	~PyUIFactory() {}

	static CControlUI* CreateControlUI(){return new CControlUI();}
	static CLabelUI* CreateLabelUI(){return new CLabelUI();}
	static CButtonUI* CreateButtonUI(){return new CButtonUI();}
	static COptionUI* CreateOptionUI(){return new COptionUI();}
	static CComboUI* CreateComboUI(){return new CComboUI();}
	static CCheckBoxUI* CreateCheckBoxUI(){return new CCheckBoxUI();}
	static CEditUI* CreateEditUI(){return new CEditUI();}
	static CProgressUI* CreateProgressUI(){return new CProgressUI();}
	static CAnimationUI* CreateAnimationUI(){return new CAnimationUI();}
	static CContainerUI* CreateContainerUI(){return new CContainerUI();}
	static CTabLayoutUI* CreateTabLayoutUI(){return new CTabLayoutUI();}
	static CHorizontalLayoutUI* CreateHorizontalLayoutUI(){return new CHorizontalLayoutUI();}
	static CVerticalLayoutUI* CreateVerticalLayoutUI(){return new CVerticalLayoutUI();}
	static CListUI* CreateListUI(){return new CListUI();}
	static CListContainerElementUI* CreateListContainerElementUI(){return new CListContainerElementUI();}
};

class PyUICast
{
public:
	PyUICast() {}
	~PyUICast() {}

	static CLabelUI* castLabelUI(CControlUI* control){return static_cast<CLabelUI*>(control);}
	static CButtonUI* castButtonUI(CControlUI* control){return static_cast<CButtonUI*>(control);}
	static COptionUI* castOptionUI(CControlUI* control){return static_cast<COptionUI*>(control);}
	static CComboUI* castComboUI(CControlUI* control){return static_cast<CComboUI*>(control);}
	static CCheckBoxUI* castCheckBoxUI(CControlUI* control){return static_cast<CCheckBoxUI*>(control);}
	static CEditUI* castEditUI(CControlUI* control){return static_cast<CEditUI*>(control);}
	static CProgressUI* castProgressUI(CControlUI* control){return static_cast<CProgressUI*>(control);}
	static CAnimationUI* castAnimationUI(CControlUI* control){return static_cast<CAnimationUI*>(control);}
	static CContainerUI* castContainerUI(CControlUI* control){return static_cast<CContainerUI*>(control);}
	static CTabLayoutUI* castTabLayoutUI(CControlUI* control){return static_cast<CTabLayoutUI*>(control);}
	static CHorizontalLayoutUI* castHorizontalLayoutUI(CControlUI* control){return static_cast<CHorizontalLayoutUI*>(control);}
	static CVerticalLayoutUI* castVerticalLayoutUI(CControlUI* control){return static_cast<CVerticalLayoutUI*>(control);}
	static CListUI* castListUI(CControlUI* control){return static_cast<CListUI*>(control);}
	static CListContainerElementUI* castListContainerElementUI(CControlUI* control){return static_cast<CListContainerElementUI*>(control);}
};

// An abstract base class
class PyUIBase : public boost::noncopyable
{
public:
	virtual ~PyUIBase() {};
	virtual LPCSTR GetSkinFile(){return NULL;};
	virtual LPCSTR GetWindowClassName(){return NULL;};	

	virtual void OnFinalMessage(ULONG hWnd){};
	virtual void InitWindow(){};;
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam){return 0;};
	virtual LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam){return 0;};
	virtual void OnNotify(LPCSTR sendor, LPCSTR sType, WPARAM wParam, LPARAM lParam){};
	virtual void OnPrepare(LPCSTR sendor, WPARAM wParam, LPARAM lParam){};
	virtual void OnExit(LPCSTR sendor, WPARAM wParam, LPARAM lParam){};
	virtual void OnTimer(LPCSTR sendor, WPARAM wParam, LPARAM lParam){};

	virtual void Show() {m_pyFrameUI->ShowWindow();};
	virtual UINT ShowModal() {return m_pyFrameUI->ShowModal();};

	virtual void SetHWnd(ULONG hWnd) { m_hWnd = hWnd;};
	virtual ULONG GetHWnd() { return m_hWnd;};
	virtual void CloseWindow() { ::PostMessage((HWND)m_hWnd, WM_CLOSE, 0L, 0L); }
	virtual void HideWindow() { ::ShowWindow((HWND)m_hWnd, SW_HIDE); }
	virtual void ExitApp() { ::ExitProcess(0); }
	ULONG ProcessMessages() { return m_pyFrameUI->ProcessMessages();}

	CControlUI* FindControl(LPCSTR ControlName)
	{
		CControlUI* pControl = m_pyFrameUI->FindControl(ControlName);
		return pControl;
	}
	// 为方便使用加入
	virtual void SetText(LPCSTR ControlName, LPCSTR caption)
	{
		CControlUI* pControl = m_pyFrameUI->FindControl(ControlName);
		pControl->SetText(caption);
	}
	// 接口增加方法:
	// 增加方法后需要在PyUIBaseWrap增加2个接口封装, 还要再app的模块定义里头加入对应的函数定义

	virtual void SetPyFrameUI(PyFrameUI *PyFrameUI) { m_pyFrameUI = PyFrameUI;};

protected:
	ULONG	m_hWnd;
	PyFrameUI* m_pyFrameUI;   // dui中实现的ui对象
};

// Familiar Boost.Python wrapper class for Base
struct PyUIBaseWrap : PyUIBase, wrapper<PyUIBase>
{
	virtual CControlUI* FindControl(LPCSTR ControlName) { return this->PyUIBase::FindControl(ControlName); }
	virtual CLabelUI* FindLabel(LPCSTR ControlName) { return (CLabelUI*)this->PyUIBase::FindControl(ControlName); }
	virtual CButtonUI* FindButtonUI(LPCSTR ControlName) { return (CButtonUI*)this->PyUIBase::FindControl(ControlName); }
	virtual COptionUI* FindOptionUI(LPCSTR ControlName) { return (COptionUI*)this->PyUIBase::FindControl(ControlName); }
	virtual CComboUI* FindComboUI(LPCSTR ControlName) { return (CComboUI*)this->PyUIBase::FindControl(ControlName); }
	virtual CCheckBoxUI* FindCheckBoxUI(LPCSTR ControlName) { return (CCheckBoxUI*)this->PyUIBase::FindControl(ControlName); }
	virtual CTextUI* FindTextUI(LPCSTR ControlName) { return (CTextUI*)this->PyUIBase::FindControl(ControlName); }
	virtual CEditUI* FindEditUI(LPCSTR ControlName) { return (CEditUI*)this->PyUIBase::FindControl(ControlName); }
	virtual CRichEditUI* FindRichEditUI(LPCSTR ControlName) { return (CRichEditUI*)this->PyUIBase::FindControl(ControlName); }
	virtual CProgressUI* FindProgressUI(LPCSTR ControlName) { return (CProgressUI*)this->PyUIBase::FindControl(ControlName); }
	virtual CAnimationUI* FindAnimationUI(LPCSTR ControlName) { return (CAnimationUI*)this->PyUIBase::FindControl(ControlName); }
	virtual CContainerUI* FindContainerUI(LPCSTR ControlName) { return (CContainerUI*)this->PyUIBase::FindControl(ControlName); }
	virtual CTabLayoutUI* FindTabLayoutUI(LPCSTR ControlName) { return (CTabLayoutUI*)this->PyUIBase::FindControl(ControlName); }
	virtual CHorizontalLayoutUI* FindHorizontalLayoutUI(LPCSTR ControlName) { return (CHorizontalLayoutUI*)this->PyUIBase::FindControl(ControlName); }
	virtual CVerticalLayoutUI* FindVerticalLayoutUI(LPCSTR ControlName) { return (CVerticalLayoutUI*)this->PyUIBase::FindControl(ControlName); }
	virtual CListUI* FindListUI(LPCSTR ControlName) { return (CListUI*)this->PyUIBase::FindControl(ControlName); }
	virtual CListContainerElementUI* FindListContainerElementUI(LPCSTR ControlName) { return (CListContainerElementUI*)this->PyUIBase::FindControl(ControlName); }
	virtual CWebBrowserUI* FindWebBrowserUI(LPCSTR ControlName) { return (CWebBrowserUI*)this->PyUIBase::FindControl(ControlName); }

	virtual ULONG ProcessMessages() { return this->PyUIBase::ProcessMessages(); }
	virtual UINT ShowModal() { return this->PyUIBase::ShowModal(); }
	UINT default_ShowModal() { return this->PyUIBase::ShowModal(); }
	virtual void Show() { this->PyUIBase::Show(); }
	void default_Show() { this->PyUIBase::Show(); }
	virtual void ExitApp()
	{
		if (override oSetHWnd = this->get_override("ExitApp"))
			oSetHWnd(); 
		else
			this->PyUIBase::ExitApp();
	}
	void default_ExitApp() { this->PyUIBase::ExitApp(); }
	virtual void HideWindow()
	{
		if (override oSetHWnd = this->get_override("HideWindow"))
			oSetHWnd(); 
		else
			this->PyUIBase::HideWindow();
	}
	void default_HideWindow() { this->PyUIBase::HideWindow(); }
	virtual void CloseWindow()
	{
		if (override oSetHWnd = this->get_override("CloseWindow"))
			oSetHWnd(); 
		else
			this->PyUIBase::CloseWindow();
	}
	void default_CloseWindow() { this->PyUIBase::CloseWindow(); }

	virtual void SetText(LPCSTR ControlName, LPCSTR caption)
	{
		if (override oSetHWnd = this->get_override("SetText"))
			oSetHWnd(ControlName, caption); 
		else
			this->PyUIBase::SetText(ControlName, caption);
	}
	virtual void default_SetText(LPCSTR ControlName, LPCSTR caption) { this->PyUIBase::SetText(ControlName, caption); }
	virtual void SetHWnd(ULONG hWnd)
	{
		if (override oSetHWnd = this->get_override("SetHWnd"))
			oSetHWnd(hWnd); 
		else
			this->PyUIBase::SetHWnd(hWnd);
	}
	void default_SetHWnd(ULONG hWnd) { this->PyUIBase::SetHWnd(hWnd); }
	virtual ULONG GetHWnd()
	{
		if (override oGetHWnd = this->get_override("GetHWnd"))
			return oGetHWnd(); 
		else
			return this->PyUIBase::GetHWnd();
	}
	ULONG default_GetHWnd() { return this->PyUIBase::GetHWnd(); }

	virtual LPCSTR GetSkinFile() { return this->get_override("GetSkinFile")(); }
	LPCSTR default_GetSkinFile() { return this->get_override("GetSkinFile")(); }
	virtual LPCSTR GetWindowClassName() { return this->get_override("GetWindowClassName")(); }
	LPCSTR default_GetWindowClassName() { return this->get_override("GetWindowClassName")(); }
	virtual void OnFinalMessage(ULONG hWnd) { this->get_override("OnFinalMessage")(hWnd); }
	void default_OnFinalMessage(ULONG hWnd) { this->get_override("OnFinalMessage")(hWnd); }
	virtual void InitWindow() { this->get_override("InitWindow")(); }
	void default_InitWindow() { this->get_override("InitWindow")(); }
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) { return this->get_override("HandleMessage")(uMsg, wParam, lParam); }
	LRESULT default_HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) { return this->PyUIBase::HandleMessage(uMsg, wParam, lParam); }
	virtual LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) { return this->get_override("HandleCustomMessage")(uMsg, wParam, lParam); }
	LRESULT default_HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) { return this->PyUIBase::HandleCustomMessage(uMsg, wParam, lParam); }
	virtual void OnNotify(LPCSTR sendor, LPCSTR sType, WPARAM wParam, LPARAM lParam) { this->get_override("OnNotify")(sendor, sType, wParam, lParam); }
	void default_OnNotify(LPCSTR sendor, LPCSTR sType, WPARAM wParam, LPARAM lParam) { this->PyUIBase::OnNotify(sendor, sType, wParam, lParam); }
	virtual void OnPrepare(LPCSTR sendor, WPARAM wParam, LPARAM lParam) { this->get_override("OnPrepare")(sendor, wParam, lParam); }
	void default_OnPrepare(LPCSTR sendor, WPARAM wParam, LPARAM lParam) { this->PyUIBase::OnPrepare(sendor, wParam, lParam); }
	virtual void OnExit(LPCSTR sendor, WPARAM wParam, LPARAM lParam) { this->get_override("OnExit")(sendor, wParam, lParam); }
	void default_OnExit(LPCSTR sendor, WPARAM wParam, LPARAM lParam) { this->PyUIBase::OnExit(sendor, wParam, lParam); }
	virtual void OnTimer(LPCSTR sendor, WPARAM wParam, LPARAM lParam) { this->get_override("OnTimer")(sendor, wParam, lParam); }
	void default_OnTimer(LPCSTR sendor, WPARAM wParam, LPARAM lParam) { this->PyUIBase::OnTimer(sendor, wParam, lParam); }
};

// 该类是python和ui的桥梁, python用createform接口通过PyFrameUI创建窗口，
// 而界面通过PyUIBase来调用python的业务逻辑
class PyFrameCreator
{
public:

	PyFrameCreator();
	~PyFrameCreator();

public:
	object PyCreateDialog(ULONG hParent, LPCSTR pyModule, LPCSTR pyClassName, LPCSTR pyFormCaption);
	object PyCreateWindow(ULONG hParent, LPCSTR pyModule, LPCSTR pyClassName, LPCSTR pyFormCaption, DWORD dwStyle, DWORD dwExStyle);
	object PyCreateForm(ULONG hParent, LPCSTR pyModule, LPCSTR pyClassName, LPCSTR pyFormCaption);
	void Show();
	UINT ShowModal();

protected:
	CDuiString m_xmlSkinFile;
	CDuiString m_pyModule; 
	CDuiString m_pyClassName;
	PyFrameUI* m_pyFrameUI;   // dui中实现的ui对象
	object m_Module;
	object m_ClassUI; 
	object m_InstanceUI;

	PyUIBase* m_pyBaseUI;  // 在python里实现的的业务对象
};

#endif // PYFRAME_HPP
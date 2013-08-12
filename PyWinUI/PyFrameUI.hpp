
#ifndef PyFrameWrap_HPP
#define PyFrameWrap_HPP

class PyUIBase;


class PyFrameUI : public WindowImplBase
{
public:
	PyFrameUI();
	~PyFrameUI();

public:
	void SetPyBaseUI(PyUIBase *frame); 
	LPCTSTR GetWindowClassName() const;	
	virtual CDuiString GetSkinFile();
	virtual CDuiString GetSkinFolder();
	virtual void OnFinalMessage(HWND hWnd);
	virtual void InitWindow();
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	virtual LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	CControlUI* FindControl(LPCSTR ControlName);

protected:	

	void Notify(TNotifyUI& msg);
	void OnPrepare(TNotifyUI& msg);
	void OnExit(TNotifyUI& msg);
	void OnTimer(TNotifyUI& msg);

	CDuiString m_xmlSkinFile;
	PyUIBase* m_frame;
};

#endif // PyFrameWrap_HPP
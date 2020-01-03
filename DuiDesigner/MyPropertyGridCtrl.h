#pragma once
#include "afxpropertygridctrl.h"

class CMyPropertyGridCtrl :
	public CMFCPropertyGridCtrl
{
public:
	CMyPropertyGridCtrl(void);
	~CMyPropertyGridCtrl(void);

	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

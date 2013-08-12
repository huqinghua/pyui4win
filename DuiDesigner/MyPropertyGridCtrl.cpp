#include "StdAfx.h"
#include "MyPropertyGridCtrl.h"

CMyPropertyGridCtrl::CMyPropertyGridCtrl(void)
{
}

CMyPropertyGridCtrl::~CMyPropertyGridCtrl(void)
{
}

BOOL CMyPropertyGridCtrl::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_DELETE)
	{	
		pMsg->wParam = VK_BACK;
		//if (m_pSel == NULL || !m_pSel->IsEnabled())
		//{
		//}
		//else
		//{
		//	ASSERT_VALID(m_pSel);

		//	if (!EditItem(m_pSel))
		//	{
		//	}
		//}

		//return TRUE;
	}
	/*else if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_BACK)
	{	

		if (m_pSel == NULL || !m_pSel->IsEnabled())
		{
		}
		else
		{
			ASSERT_VALID(m_pSel);

			if (!EditItem(m_pSel))
			{
			}
		}

		return TRUE;
	}*/

	return CMFCPropertyGridCtrl::PreTranslateMessage(pMsg);
}
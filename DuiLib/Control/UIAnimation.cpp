#include "StdAfx.h"
#include "UIAnimation.h"

namespace DuiLib
{
	CAnimationUI::CAnimationUI(void) : 
		m_dwFrameInterval(0), 
		m_dwTimerID(0),
		m_nFrameCount(0),
		m_nFrameIndex(0)
	{
	}

	CAnimationUI::~CAnimationUI(void)
	{
	}

	LPCTSTR CAnimationUI::GetClass() const
	{
		return _T("AnimationUI");
	}

	LPVOID CAnimationUI::GetInterface(LPCTSTR pstrName)
	{
		if( _tcscmp(pstrName, _T("Animation")) == 0 ) return static_cast<CAnimationUI*>(this);
		return CControlUI::GetInterface(pstrName);
	}

	void CAnimationUI::SetFrameInterval(DWORD interval)
	{
		m_dwFrameInterval = interval;
	}

	void CAnimationUI::SetFrameSize(SIZE frameSize)
	{
		m_sizeFrame = frameSize;
	}

	void CAnimationUI::StartAnimation()
	{
		if (m_dwTimerID == 0)
			m_dwTimerID = GetTickCount();
		m_pManager->SetTimer(this, m_dwTimerID, 50);
	}

	void CAnimationUI::StopAnimation()
	{
		ASSERT(m_dwTimerID);
		m_pManager->KillTimer(this, m_dwTimerID);
		m_dwTimerID = -1;
	}

	void CAnimationUI::DoInit()
	{
		if (m_bEnabled) StartAnimation();
	}

	void CAnimationUI::SetAnimationImg(LPCTSTR pStrImage)
	{
		if( m_sAnimationImage == pStrImage ) return;
		m_sAnimationImage = pStrImage;
		if (m_sAnimationImage.IsEmpty()) return; 
		const TImageInfo* data = NULL;
		data = m_pManager->GetImageEx((LPCTSTR)m_sAnimationImage, NULL, 0);
		if( !data ) return;    

		m_nFrameCount = data->nX / m_sizeFrame.cx;
	}

	void CAnimationUI::PaintBkImage(HDC hDC)
	{
		//if (!m_bEnabled) return;
		if( m_sAnimationImage.IsEmpty() ) return;

		RECT rcBmpPart = {0};
		RECT rcCorners = {0};
		rcBmpPart.left = m_nFrameIndex * m_sizeFrame.cx;
		rcBmpPart.top = 0;
		rcBmpPart.right = (m_nFrameIndex + 1)* m_sizeFrame.cx - 1;
		rcBmpPart.bottom = m_sizeFrame.cy;

		CDuiString nullString;
		CRenderEngine::DrawImage(hDC, m_pManager, m_rcItem, m_rcPaint, m_sAnimationImage, nullString,
			m_rcItem, rcBmpPart, rcCorners, false, 255, false, false, false);
	}

	void CAnimationUI::SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue)
	{
		if( _tcscmp(pstrName, _T("frameinterval")) == 0 ) {
			LPTSTR pstr = NULL;
			DWORD interval = _tcstoul(pstrValue, &pstr, 10);
			SetFrameInterval(interval);
		}    
		else if( _tcscmp(pstrName, _T("framesize")) == 0 ) {
			LPTSTR pstr = NULL;
			SIZE frame;
			frame.cx = _tcstol(pstrValue, &pstr, 10);  ASSERT(pstr);    
			frame.cy = _tcstol(pstr + 1, &pstr, 10);    ASSERT(pstr);    
			SetFrameSize(frame);
		}
		else if( _tcscmp(pstrName, _T("animationimage")) == 0 ) {
			SetAnimationImg(pstrValue);
		} 
		else CControlUI::SetAttribute(pstrName, pstrValue);
	}


	void CAnimationUI::DoEvent(TEventUI& event)
	{
		if( event.Type == UIEVENT_TIMER && event.wParam == m_dwTimerID) {
			ASSERT(m_nFrameCount);
			m_nFrameIndex = (++m_nFrameIndex) % m_nFrameCount;
			Invalidate();
			return;
		}
		
		CControlUI::DoEvent(event);
	}
}
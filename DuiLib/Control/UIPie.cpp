#include "StdAfx.h"
#include "UIPie.h"
#include <gdiplus.h>
#include <atlbase.h>
#include <atlcoll.h>
#include <atlstr.h>
#include <strsafe.h>
#include <atlapp.h>
#include <atlmisc.h>
namespace DuiLib
{
	CPieUI::CPieUI(void)
	{
	}

	CPieUI::~CPieUI(void)
	{
		Gdiplus::GdiplusShutdown(m_gdiplusToken);
	}

	LPVOID CPieUI::GetInterface(LPCTSTR pstrName)
	{
		if( _tcscmp(pstrName, _T("Pie")) == 0 ) return static_cast<CPieUI*>(this);
		return CControlUI::GetInterface(pstrName);
	}


	LPCTSTR CPieUI::GetClass() const
	{
		return _T("PieUI");
	}

	void CPieUI::SetArc1Corrdinate(SIZE coordinate)
	{
		m_coordinate = coordinate;
	}

	void CPieUI::SetArc1Radius(DWORD dwRadius)
	{
		m_dwRadius = dwRadius;

	}

	void CPieUI::SetArc1Color(DWORD dwColor)
	{
		m_dwColor = dwColor;

	}

	void CPieUI::SetArc1Angle(DWORD dwStartAngle, DWORD dwEndAngle)
	{
		m_dwStartAngle = dwStartAngle;
		m_dwEndAngle = dwEndAngle;
	}

	void CPieUI::DoInit()
	{
		Gdiplus::GdiplusStartupInput gdiplusStartupInput;
		Gdiplus::GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);
	}

	void CPieUI::PaintBkImage(HDC hDC)
	{
		//MoveToEx(hDC, (int) m_coordinate.cx + m_cXY.cx, (int) m_coordinate.cy + m_cXY.cy, (LPPOINT) NULL); 
		//AngleArc(hDC, m_coordinate.cx + m_cXY.cx, m_coordinate.cy + m_cXY.cy, m_dwRadius, m_dwStartAngle, m_dwEndAngle);
		//MoveToEx(hDC, (int) m_coordinate.cx + m_cXY.cx, (int) m_coordinate.cy + m_cXY.cy, (LPPOINT) NULL); 

		Bitmap* mBtmap;
		Graphics* graphics;

		mBtmap = new Bitmap(m_dwRadius * 2 + 1, m_dwRadius * 2 + 1);
		graphics = Graphics::FromImage(mBtmap);

		graphics->SetSmoothingMode(SmoothingModeHighQuality);

		SolidBrush crGradient(Color(GetRValue(m_dwColor), GetGValue(m_dwColor), GetBValue(m_dwColor)));
		Pen pnHighLight(Color(GetRValue(m_dwColor), GetGValue(m_dwColor), GetBValue(m_dwColor)));

		graphics->FillPie(&crGradient, 
			RectF((REAL)0, 
			(REAL)0, 
			(REAL)m_dwRadius * 2, 
			(REAL)m_dwRadius * 2), 
			(REAL)m_dwStartAngle, 
			(REAL)m_dwEndAngle);
		//graphics->DrawPie(&pnHighLight, 
		//	RectF((REAL)0, 
		//	(REAL)0, 
		//	(REAL)m_dwRadius * 2, 
		//	(REAL)m_dwRadius * 2), 
		//	(REAL)m_dwStartAngle, 
		//	(REAL)m_dwEndAngle);
		delete graphics;
		graphics = NULL;

		Graphics gr(hDC);
		//CachedBitmap* btmp = new CachedBitmap(mBtmap, &gr);

		gr.DrawImage(mBtmap, (int)(m_rcItem.left + m_coordinate.cx - m_dwRadius), m_rcItem.top + m_coordinate.cy - m_dwRadius);	
		if (mBtmap){
			delete mBtmap;
			mBtmap = NULL;
		}
	}

	void CPieUI::SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue)
	{
		if( _tcscmp(pstrName, _T("corrdinate")) == 0 ) {
			LPTSTR pstr = NULL;
			SIZE frame;
			frame.cx = _tcstol(pstrValue, &pstr, 10);  ASSERT(pstr);    
			frame.cy = _tcstol(pstr + 1, &pstr, 10);    ASSERT(pstr);    
			SetArc1Corrdinate(frame);
		}    
		else if( _tcscmp(pstrName, _T("radius")) == 0 ) {
			LPTSTR pstr = NULL;
			DWORD dwRadius = _tcstoul(pstrValue, &pstr, 10);
			SetArc1Radius(dwRadius);
		}
		else if( _tcscmp(pstrName, _T("piecolor")) == 0 ) {
			if( *pstrValue == _T('#')) pstrValue = ::CharNext(pstrValue);
			LPTSTR pstr = NULL;
			DWORD clrColor = _tcstoul(pstrValue, &pstr, 16);
			SetArc1Color(clrColor);
		} 
		else if( _tcscmp(pstrName, _T("angle")) == 0 ) {
			LPTSTR pstr = NULL;
			DWORD dwStartAngle = _tcstol(pstrValue, &pstr, 10);  ASSERT(pstr);    
			DWORD dwEndAngle = _tcstol(pstr + 1, &pstr, 10);    ASSERT(pstr);    
			SetArc1Angle(dwStartAngle, dwEndAngle);
		} 
		else CControlUI::SetAttribute(pstrName, pstrValue);
	}


	void CPieUI::DoEvent(TEventUI& event)
	{
		CControlUI::DoEvent(event);
	}
}

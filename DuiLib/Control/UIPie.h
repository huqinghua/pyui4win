#pragma once

namespace DuiLib
{
	class UILIB_API CPieUI : public CControlUI
	{
	public:
		CPieUI(void);
		~CPieUI(void);

		LPCTSTR GetClass() const;
		LPVOID GetInterface(LPCTSTR pstrName);

		void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

		void SetArc1Corrdinate(SIZE coordinate);
		void SetArc1Radius(DWORD dwRadius);
		void SetArc1Color(DWORD dwColor);
		void SetArc1Angle(DWORD dwStartAngle, DWORD dwEndAngle);

		void DoInit();

		virtual void DoEvent(TEventUI& event);
		virtual void PaintBkImage(HDC hDC);

	private:
		DWORD m_dwRadius;
		DWORD m_dwColor;
		SIZE m_coordinate; // 
		DWORD m_dwStartAngle; 
		DWORD m_dwEndAngle;
		ULONG_PTR m_gdiplusToken;
	};
}	// namespace DuiLib

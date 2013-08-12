#pragma once

namespace DuiLib
{
	class UILIB_API CAnimationUI : public CControlUI
	{
	public:
		CAnimationUI(void);
		~CAnimationUI(void);

		LPCTSTR GetClass() const;
		LPVOID GetInterface(LPCTSTR pstrName);

		void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

		void SetFrameInterval(DWORD interval);
		DWORD GetFrameInterval(){ return m_dwFrameInterval;}
		void SetFrameSize(SIZE frameSize);
		SIZE GetFrameSize() { return m_sizeFrame; }
		void StartAnimation();
		void StopAnimation();
		void SetAnimationImg(LPCTSTR pStrImage);
		LPCTSTR GetAnimationImg() { return m_sAnimationImage; }
		void DoInit();

		virtual void DoEvent(TEventUI& event);
		virtual void PaintBkImage(HDC hDC);

	private:
		DWORD m_dwFrameInterval;
		SIZE m_sizeFrame; // 获取每帧大小
		CDuiString m_sAnimationImage;
		DWORD m_dwTimerID;
		int m_nFrameIndex;
		int m_nFrameCount; // 帧总数
	};

}	// namespace DuiLib
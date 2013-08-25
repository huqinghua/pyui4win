#include "stdafx.h"


#ifdef _DEBUG
#undef _DEBUG
#include <Python.h>
#define _DEBUG
#else
#include <Python.h>
#endif

#include<boost/python.hpp>
#include "PyFrameCreator.hpp"
#include "Win32Api.h"
#include "PyModuleImport.h"
#include "PyException.h"
#include "duilib-python.h"

using namespace std;
using namespace DuiLib;
using namespace boost::python;

typedef boost::shared_ptr < PyFrameCreator > PyFrame_ptr;  
typedef boost::shared_ptr < CControlUI > PyControlUI_ptr;  
typedef boost::shared_ptr < CLabelUI > PyLabelUI_ptr;  
typedef boost::shared_ptr < CButtonUI > PyButtonUI_ptr;  
typedef boost::shared_ptr < COptionUI > PyOptionUI_ptr;  
typedef boost::shared_ptr < CCheckBoxUI > PyCheckBoxUI_ptr;  
typedef boost::shared_ptr < CProgressUI > PyProgressUI_ptr;  
typedef boost::shared_ptr < CAnimationUI > PyAnimationUI_ptr;  
typedef boost::shared_ptr < CHorizontalLayoutUI > PyHorizontalLayoutUI_ptr;  
typedef boost::shared_ptr < CVerticalLayoutUI > PyVerticalLayoutUI_ptr;  
typedef boost::shared_ptr < CTabLayoutUI > PyTabLayoutUI_ptr;  
typedef boost::shared_ptr < CListUI > PyListUI_ptr;  
typedef boost::shared_ptr < CListContainerElementUI > PyListContainerElementUI_ptr;  
typedef boost::shared_ptr < PyUIFactory > PyUIFactory_ptr;  

BOOST_PYTHON_MODULE(PyUI)
{

	class_<SIZE>("SIZE")
		.def_readwrite("cx", &SIZE::cx)
		.def_readwrite("cy", &SIZE::cy)
		;

	class_<POINT>("POINT")
		.def_readwrite("x", &POINT::x)
		.def_readwrite("y", &POINT::y)
		;

	class_<RECT>("RECT")
		.def_readwrite("left", &RECT::left)
		.def_readwrite("top", &RECT::top)
		.def_readwrite("right", &RECT::right)
		.def_readwrite("bottom", &RECT::bottom)
		;

	CControlUI*    (CPaintManagerUI::*FindControlByPointRoot)(POINT) const              = &CPaintManagerUI::FindControl;
	CControlUI*    (CPaintManagerUI::*FindControlByNameRoot)(LPCTSTR) const     = &CPaintManagerUI::FindControl;
	class_<CPaintManagerUI, boost::noncopyable>("CPaintManagerUI")
		.def("GetRoot", &CPaintManagerUI::GetRoot, return_value_policy<reference_existing_object>())
		.def("FindSubControlByPoint", &CPaintManagerUI::FindSubControlByPoint, return_value_policy<reference_existing_object>())
		.def("FindSubControlByName", &CPaintManagerUI::FindSubControlByName, return_value_policy<reference_existing_object>())
		.def("FindSubControlByClass", &CPaintManagerUI::FindSubControlByClass, return_value_policy<reference_existing_object>())
		.def("FindControl", FindControlByPointRoot, return_value_policy<reference_existing_object>())
		.def("FindControl", FindControlByNameRoot, return_value_policy<reference_existing_object>())
		.def("MessageLoop", &CPaintManagerUI::MessageLoop)
		. staticmethod("MessageLoop") 
		; 

	void    (CControlUI::*SetBorderSizeBySize)(int) = &CControlUI::SetBorderSize;
	void    (CControlUI::*SetBorderSizeByRect)(RECT) = &CControlUI::SetBorderSize;
	class_<CControlUI, boost::noncopyable>("CControlUI")
		.def("SetName", &CControlUI::SetName)
		.def("GetName", &CControlUI::GetName)
		.def("GetClass", &CControlUI::GetClass)
		.def("GetControlFlags", &CControlUI::GetControlFlags)
		.def("Activate", &CControlUI::Activate)
		.def("GetManager", &CControlUI::GetManager, return_value_policy<reference_existing_object>())
		.def("SetManager", &CControlUI::SetManager)
		.def("GetParent", &CControlUI::GetParent, return_value_policy<reference_existing_object>())
		.def("SetText", &CControlUI::SetText)
		.def("GetText", &CControlUI::GetText)
		.def("SetAttribute", &CControlUI::SetAttribute)
		.def("IsVisible", &CControlUI::IsVisible)
		.def("SetVisible", &CControlUI::SetVisible)
		.def("SetInternVisible", &CControlUI::SetInternVisible)
		.def("IsEnabled", &CControlUI::IsEnabled)
		.def("SetEnabled", &CControlUI::SetEnabled)
		.def("IsMouseEnabled", &CControlUI::IsMouseEnabled)
		.def("SetMouseEnabled", &CControlUI::SetMouseEnabled)
		.def("IsKeyboardEnabled", &CControlUI::IsKeyboardEnabled)
		.def("SetKeyboardEnabled", &CControlUI::SetKeyboardEnabled)
		.def("IsFocused", &CControlUI::IsFocused)
		.def("SetFocus", &CControlUI::SetFocus)
		.def("IsFloat", &CControlUI::IsFloat)
		.def("SetFloat", &CControlUI::SetFloat)
		.def("ApplyAttributeList", &CControlUI::ApplyAttributeList, return_value_policy<reference_existing_object>())
		.def("Invalidate", &CControlUI::Invalidate)
		.def("IsUpdateNeeded", &CControlUI::IsUpdateNeeded)
		.def("NeedUpdate", &CControlUI::NeedUpdate)
		.def("NeedParentUpdate", &CControlUI::NeedParentUpdate)
		.def("GetBkColor", &CControlUI::GetBkColor)
		.def("SetBkColor", &CControlUI::SetBkColor)
		.def("GetBkColor2", &CControlUI::GetBkColor2)
		.def("SetBkColor2", &CControlUI::SetBkColor2)
		.def("GetBkColor3", &CControlUI::GetBkColor3)
		.def("SetBkColor3", &CControlUI::SetBkColor3)
		.def("GetBkImage", &CControlUI::GetBkImage)
		.def("SetBkImage", &CControlUI::SetBkImage)
		.def("GetFocusBorderColor", &CControlUI::GetFocusBorderColor)
		.def("SetFocusBorderColor", &CControlUI::SetFocusBorderColor)
		.def("IsColorHSL", &CControlUI::IsColorHSL)
		.def("SetColorHSL", &CControlUI::SetColorHSL)
		.def("GetBorderRound", &CControlUI::GetBorderRound)
		.def("SetBorderRound", &CControlUI::SetBorderRound)
		.def("GetBorderSize", &CControlUI::GetBorderSize)
		.def("SetBorderSize", SetBorderSizeBySize)
		.def("SetBorderSize", SetBorderSizeByRect)
		.def("GetBorderColor", &CControlUI::GetBorderColor)
		.def("SetBorderColor", &CControlUI::SetBorderColor)
		.def("GetLeftBorderSize", &CControlUI::GetLeftBorderSize)
		.def("SetLeftBorderSize", &CControlUI::SetLeftBorderSize)
		.def("GetTopBorderSize", &CControlUI::GetTopBorderSize)
		.def("SetTopBorderSize", &CControlUI::SetTopBorderSize)
		.def("GetRightBorderSize", &CControlUI::GetRightBorderSize)
		.def("SetRightBorderSize", &CControlUI::SetRightBorderSize)
		.def("GetBottomBorderSize", &CControlUI::GetBottomBorderSize)
		.def("SetBottomBorderSize", &CControlUI::SetBottomBorderSize)
		.def("GetBorderStyle", &CControlUI::GetBorderStyle)
		.def("SetBorderStyle", &CControlUI::SetBorderStyle)
		.def("GetBottomBorderSize", &CControlUI::GetBottomBorderSize)
		.def("GetPos", &CControlUI::GetPos, return_value_policy<reference_existing_object>())
		.def("GetWidth", &CControlUI::GetWidth)
		.def("GetHeight", &CControlUI::GetHeight)
		.def("GetX", &CControlUI::GetX)
		.def("GetY", &CControlUI::GetY)
		.def("GetPadding", &CControlUI::GetPadding)
		.def("SetPadding", &CControlUI::SetPadding)
		.def("GetFixedXY", &CControlUI::GetFixedXY)
		.def("SetFixedXY", &CControlUI::SetFixedXY)
		.def("GetFixedWidth", &CControlUI::GetFixedWidth)
		.def("SetFixedWidth", &CControlUI::SetFixedWidth)
		.def("GetFixedHeight", &CControlUI::GetFixedHeight)
		.def("SetFixedHeight", &CControlUI::SetFixedHeight)
		.def("GetMinWidth", &CControlUI::GetMinWidth)
		.def("SetMinWidth", &CControlUI::SetMinWidth)
		.def("GetMaxWidth", &CControlUI::GetMaxWidth)
		.def("SetMaxWidth", &CControlUI::SetMaxWidth)
		.def("GetMinHeight", &CControlUI::GetMinHeight)
		.def("SetMinHeight", &CControlUI::SetMinHeight)
		.def("GetMaxHeight", &CControlUI::GetMaxHeight)
		.def("SetMaxHeight", &CControlUI::SetMaxHeight)
		.def("SetRelativePos", &CControlUI::SetRelativePos)
		.def("SetRelativeParentSize", &CControlUI::SetRelativeParentSize)
		.def("IsRelativePos", &CControlUI::IsRelativePos)
		.def("GetToolTip", &CControlUI::GetToolTip)
		.def("SetToolTip", &CControlUI::SetToolTip)
		.def("SetToolTipWidth", &CControlUI::SetToolTipWidth)
		.def("GetToolTipWidth", &CControlUI::GetToolTipWidth)
		; 

	class_<CContainerUI, bases<CControlUI>, boost::noncopyable>("CContainerUI")
		.def("GetItemAt", &CContainerUI::GetItemAt, return_value_policy<reference_existing_object>())
		.def("GetItemIndex", &CContainerUI::GetItemIndex)
		.def("SetItemIndex", &CContainerUI::SetItemIndex)
		.def("GetCount", &CContainerUI::GetCount)
		.def("Add", &CContainerUI::Add)
		.def("AddAt", &CContainerUI::AddAt)
		.def("Remove", &CContainerUI::Remove)
		.def("RemoveAt", &CContainerUI::RemoveAt)
		.def("RemoveAll", &CContainerUI::RemoveAll)
		; 


	CControlUI* (CDialogBuilder::*Create4Py)(TCHAR*, LPCTSTR, CPaintManagerUI* , CControlUI* ) = &CDialogBuilder::Create;
	class_<CDialogBuilder>("CDialogBuilder")
		.def("Create", Create4Py, return_value_policy<reference_existing_object>())
		;

	CControlUI* Create(TCHAR *xml, LPCTSTR type = NULL, 
		CPaintManagerUI* pManager = NULL, CControlUI* pParent = NULL);
	class_<CLabelUI, bases<CControlUI>, boost::noncopyable>("CLabelUI")
		.def("IsShowHtml", &CLabelUI::IsShowHtml)
		.def("SetShowHtml", &CLabelUI::SetShowHtml)
		.def("SetFont", &CLabelUI::SetFont)
		.def("GetFont", &CLabelUI::GetFont)
		;

	class_<CButtonUI, bases<CLabelUI>, boost::noncopyable>("CButtonUI")
		.def("GetControlFlags", &CButtonUI::GetControlFlags)
		.def("SetEnabled", &CButtonUI::SetEnabled)
		; 

	class_<COptionUI, bases<CButtonUI>, boost::noncopyable>("COptionUI")
		.def("IsSelected", &COptionUI::IsSelected)
		.def("SetEnabled", &COptionUI::SetEnabled)
		.def("GetGroup", &COptionUI::GetGroup)
		.def("SetGroup", &COptionUI::SetGroup)
		.def("Selected", &COptionUI::Selected)
		; 	

	class_<CCheckBoxUI, bases<COptionUI>, boost::noncopyable>("CCheckBoxUI")
		.def("SetCheck", &CCheckBoxUI::SetCheck)
		.def("GetCheck", &CCheckBoxUI::GetCheck)
		; 

	class_<CComboUI, bases<CContainerUI>, boost::noncopyable>("CComboUI")
		.def("GetControlFlags", &CComboUI::GetControlFlags)
		.def("SetEnabled", &CComboUI::SetEnabled)
		.def("GetDropBoxAttributeList", &CComboUI::GetDropBoxAttributeList)
		.def("SetDropBoxAttributeList", &CComboUI::SetDropBoxAttributeList)
		.def("GetCurSel", &CComboUI::GetCurSel)
		.def("SelectItem", &CComboUI::SelectItem)
		.def("SetItemIndex", &CComboUI::SetItemIndex)
		.def("Add", &CComboUI::Add)
		.def("AddAt", &CComboUI::AddAt)
		.def("Remove", &CComboUI::Remove)
		.def("RemoveAt", &CComboUI::RemoveAt)
		.def("RemoveAll", &CComboUI::RemoveAll)
		.def("Activate", &CComboUI::Activate)
		; 

	class_<CProgressUI, bases<CLabelUI>, boost::noncopyable>("CProgressUI")
		.def("GetValue", &CProgressUI::GetValue)
		.def("SetValue", &CProgressUI::SetValue)
		.def("GetMinValue", &CProgressUI::GetMinValue)
		.def("SetMinValue", &CProgressUI::SetMinValue)
		.def("GetMaxValue", &CProgressUI::GetMaxValue)
		.def("SetMaxValue", &CProgressUI::SetMaxValue)
		; 

	class_<CTextUI, bases<CLabelUI>, boost::noncopyable>("CTextUI")
		.def("SetEnabled", &CTextUI::SetEnabled)
		.def("GetLinkContent", &CTextUI::GetLinkContent, return_value_policy<reference_existing_object>())
		; 

	class_<CEditUI, bases<CLabelUI>, boost::noncopyable>("CEditUI")
		.def("SetEnabled", &CEditUI::SetEnabled)
		.def("SetText", &CEditUI::SetText)
		.def("SetMaxChar", &CEditUI::SetMaxChar)
		.def("GetMaxChar", &CEditUI::GetMaxChar)
		.def("SetReadOnly", &CEditUI::SetReadOnly)
		.def("IsReadOnly", &CEditUI::IsReadOnly)
		.def("SetPasswordMode", &CEditUI::SetPasswordMode)
		.def("IsPasswordMode", &CEditUI::IsPasswordMode)
		.def("SetPasswordChar", &CEditUI::SetPasswordChar)
		.def("GetPasswordChar", &CEditUI::GetPasswordChar)
		.def("SetNumberOnly", &CEditUI::SetNumberOnly)
		.def("IsNumberOnly", &CEditUI::IsNumberOnly)
		.def("GetWindowStyls", &CEditUI::GetWindowStyls)
		; 

	class_<CAnimationUI, bases<CControlUI>, boost::noncopyable>("CAnimationUI")
		.def("StartAnimation", &CAnimationUI::StartAnimation)
		.def("StopAnimation", &CAnimationUI::StopAnimation)
		; 

	class_<CRichEditUI, bases<CContainerUI>, boost::noncopyable>("CRichEditUI")
		.def("SetText", &CRichEditUI::SetText)
		.def("SetSelAll", &CRichEditUI::SetSelAll)
		.def("SetSelNone", &CRichEditUI::SetSelNone)
		.def("GetSelText", &CRichEditUI::GetSelText)
		.def("AppendText", &CRichEditUI::AppendText)
		; 

	class_<CHorizontalLayoutUI, bases<CContainerUI>, boost::noncopyable>("CHorizontalLayoutUI")
		.def("GetControlFlags", &CHorizontalLayoutUI::GetControlFlags)
		.def("SetSepWidth", &CHorizontalLayoutUI::SetSepWidth)
		.def("GetSepWidth", &CHorizontalLayoutUI::GetSepWidth)
		.def("SetSepImmMode", &CHorizontalLayoutUI::SetSepImmMode)
		.def("IsSepImmMode", &CHorizontalLayoutUI::IsSepImmMode)
		; 

	class_<CVerticalLayoutUI, bases<CContainerUI>, boost::noncopyable>("CVerticalLayoutUI")
		.def("GetControlFlags", &CVerticalLayoutUI::GetControlFlags)
		.def("SetSepHeight", &CVerticalLayoutUI::SetSepHeight)
		.def("GetSepHeight", &CVerticalLayoutUI::GetSepHeight)
		.def("SetSepImmMode", &CVerticalLayoutUI::SetSepImmMode)
		.def("IsSepImmMode", &CVerticalLayoutUI::IsSepImmMode)
		; 

	bool    (CTabLayoutUI::*SelectItemByNo)(int)              = &CTabLayoutUI::SelectItem;
	bool    (CTabLayoutUI::*SelectItemByControl)(CControlUI*)      = &CTabLayoutUI::SelectItem;
	class_<CTabLayoutUI, bases<CContainerUI>, boost::noncopyable>("CTabLayoutUI")
		.def("Add", &CTabLayoutUI::Add)
		.def("AddAt", &CTabLayoutUI::AddAt)
		.def("Remove", &CTabLayoutUI::Remove)
		.def("RemoveAll", &CTabLayoutUI::RemoveAll)
		.def("GetCurSel", &CTabLayoutUI::GetCurSel)
		.def("SelectItem", SelectItemByNo)
		.def("SelectItem", SelectItemByControl)
		; 

	class_<CListUI, bases<CVerticalLayoutUI>, boost::noncopyable>("CListUI")
		.def("GetControlFlags", &CListUI::GetControlFlags)
		.def("GetCurSel", &CListUI::GetCurSel)
		.def("SelectItem", &CListUI::SelectItem)
		.def("GetItemAt", &CListUI::GetItemAt, return_value_policy<reference_existing_object>())
		.def("GetItemIndex", &CListUI::GetItemIndex)
		.def("SetItemIndex", &CListUI::SetItemIndex)
		.def("GetCount", &CListUI::GetCount)
		.def("Add", &CListUI::Add)
		.def("AddAt", &CListUI::AddAt)
		.def("Remove", &CListUI::Remove)
		.def("RemoveAt", &CListUI::RemoveAt)
		.def("RemoveAll", &CListUI::RemoveAll)
		.def("EnsureVisible", &CListUI::EnsureVisible)
		.def("SetMultiExpanding", &CListUI::SetMultiExpanding)
		.def("GetExpandedItem", &CListUI::GetExpandedItem)
		.def("ExpandItem", &CListUI::ExpandItem)
		; 

	class_<CListContainerElementUI, bases<CContainerUI>, boost::noncopyable>("CListContainerElementUI")
		.def("GetControlFlags", &CListContainerElementUI::GetControlFlags)
		.def("GetIndex", &CListContainerElementUI::GetIndex)
		.def("SetIndex", &CListContainerElementUI::SetIndex)
		.def("SetOwner", &CListContainerElementUI::SetOwner)
		.def("SetVisible", &CListContainerElementUI::SetVisible)
		.def("SetEnabled", &CListContainerElementUI::SetEnabled)
		.def("IsSelected", &CListContainerElementUI::IsSelected)
		.def("Select", &CListContainerElementUI::Select)
		.def("IsExpanded", &CListContainerElementUI::IsExpanded)
		.def("Expand", &CListContainerElementUI::Expand)
		.def("Invalidate", &CListContainerElementUI::Invalidate)
		; 

	class_<CWebBrowserUI, bases<CControlUI>, boost::noncopyable>("CWebBrowserUI")
		.def("NavigateUrl", &CWebBrowserUI::NavigateUrl)
		.def("Navigate2", &CWebBrowserUI::Navigate2)
		.def("Refresh", &CWebBrowserUI::Refresh)
		.def("Refresh2", &CWebBrowserUI::Refresh2)
		.def("GoBack", &CWebBrowserUI::GoBack)
		.def("GoForward", &CWebBrowserUI::GoForward)
		.def("SetHomePage", &CWebBrowserUI::SetHomePage)
		.def("GetHomePage", &CWebBrowserUI::GetHomePage)
		.def("NavigateHomePage", &CWebBrowserUI::NavigateHomePage)
		.def("DoCreateControl", &CWebBrowserUI::DoCreateControl)
		;

	class_<PyUIFactory>("PyUIFactory")
		.def("CreateControlUI", &PyUIFactory::CreateControlUI, return_value_policy<reference_existing_object>())
		. staticmethod("CreateControlUI") 
		.def("CreateLabelUI", &PyUIFactory::CreateLabelUI, return_value_policy<reference_existing_object>())
		. staticmethod("CreateLabelUI") 
		.def("CreateButtonUI", &PyUIFactory::CreateButtonUI, return_value_policy<reference_existing_object>())
		. staticmethod("CreateButtonUI") 
		.def("CreateOptionUI", &PyUIFactory::CreateOptionUI, return_value_policy<reference_existing_object>())
		. staticmethod("CreateOptionUI") 
		.def("CreateCheckBoxUI", &PyUIFactory::CreateCheckBoxUI, return_value_policy<reference_existing_object>())
		. staticmethod("CreateCheckBoxUI") 
		.def("CreateEditUI", &PyUIFactory::CreateEditUI, return_value_policy<reference_existing_object>())
		. staticmethod("CreateEditUI") 
		.def("CreateProgressUI", &PyUIFactory::CreateProgressUI, return_value_policy<reference_existing_object>())
		. staticmethod("CreateProgressUI") 
		.def("CreateAnimationUI", &PyUIFactory::CreateAnimationUI, return_value_policy<reference_existing_object>())
		. staticmethod("CreateAnimationUI") 
		.def("CreateContainerUI", &PyUIFactory::CreateContainerUI, return_value_policy<reference_existing_object>())
		. staticmethod("CreateContainerUI") 
		.def("CreateHorizontalLayoutUI", &PyUIFactory::CreateHorizontalLayoutUI, return_value_policy<reference_existing_object>())
		. staticmethod("CreateHorizontalLayoutUI") 
		.def("CreateVerticalLayoutUI", &PyUIFactory::CreateVerticalLayoutUI, return_value_policy<reference_existing_object>())
		. staticmethod("CreateVerticalLayoutUI") 
		.def("CreateTabLayoutUI", &PyUIFactory::CreateTabLayoutUI, return_value_policy<reference_existing_object>())
		. staticmethod("CreateTabLayoutUI") 
		.def("CreateListUI", &PyUIFactory::CreateListUI, return_value_policy<reference_existing_object>())
		. staticmethod("CreateListUI") 
		.def("CreateListContainerElementUI", &PyUIFactory::CreateListContainerElementUI, return_value_policy<reference_existing_object>())
		. staticmethod("CreateListContainerElementUI") 
		; 

	class_<PyUICast>("PyUICast")
		.def("castLabelUI", &PyUICast::castLabelUI, return_value_policy<reference_existing_object>())
		. staticmethod("castLabelUI") 
		.def("castButtonUI", &PyUICast::castButtonUI, return_value_policy<reference_existing_object>())
		. staticmethod("castButtonUI") 
		.def("castOptionUI", &PyUICast::castOptionUI, return_value_policy<reference_existing_object>())
		. staticmethod("castOptionUI") 
		.def("castCheckBoxUI", &PyUICast::castCheckBoxUI, return_value_policy<reference_existing_object>())
		. staticmethod("castCheckBoxUI") 
		.def("castEditUI", &PyUICast::castEditUI, return_value_policy<reference_existing_object>())
		. staticmethod("castEditUI") 
		.def("castProgressUI", &PyUICast::castProgressUI, return_value_policy<reference_existing_object>())
		. staticmethod("castProgressUI") 
		.def("castAnimationUI", &PyUICast::castAnimationUI, return_value_policy<reference_existing_object>())
		. staticmethod("castAnimationUI") 
		.def("castHorizontalLayoutUI", &PyUICast::castHorizontalLayoutUI, return_value_policy<reference_existing_object>())
		. staticmethod("castHorizontalLayoutUI") 
		.def("castContainerUI", &PyUICast::castContainerUI, return_value_policy<reference_existing_object>())
		. staticmethod("castContainerUI") 
		.def("castVerticalLayoutUI", &PyUICast::castVerticalLayoutUI, return_value_policy<reference_existing_object>())
		. staticmethod("castVerticalLayoutUI") 
		.def("castTabLayoutUI", &PyUICast::castTabLayoutUI, return_value_policy<reference_existing_object>())
		. staticmethod("castTabLayoutUI") 
		.def("castListUI", &PyUICast::castListUI, return_value_policy<reference_existing_object>())
		. staticmethod("castListUI") 
		.def("castListContainerElementUI", &PyUICast::castListContainerElementUI, return_value_policy<reference_existing_object>())
		. staticmethod("castListContainerElementUI") 
		; 

	class_<PyUIBaseWrap, boost::noncopyable>("PyUIBase")
		// 方便使用的通用函数
		.def("SetHWnd", &PyUIBaseWrap::SetHWnd)
		.def("GetHWnd", &PyUIBaseWrap::GetHWnd)
		.def("CloseWindow", &PyUIBaseWrap::CloseWindow)
		.def("HideWindow", &PyUIBaseWrap::HideWindow)
		.def("ExitApp", &PyUIBaseWrap::ExitApp, &PyUIBaseWrap::default_ExitApp)	
		.def("ProcessMessages", &PyUIBaseWrap::ProcessMessages)

		// 界面皮肤
		.def("GetSkinFile", &PyUIBaseWrap::GetSkinFile, &PyUIBaseWrap::default_GetSkinFile)
		// 界面显示
		.def("SetText", &PyUIBaseWrap::SetText)
		.def("FindControl", &PyUIBaseWrap::FindControl, return_value_policy<reference_existing_object>())
		.def("FindLabel", &PyUIBaseWrap::FindLabel, return_value_policy<reference_existing_object>())
		.def("FindButtonUI", &PyUIBaseWrap::FindButtonUI, return_value_policy<reference_existing_object>())
		.def("FindOptionUI", &PyUIBaseWrap::FindOptionUI, return_value_policy<reference_existing_object>())
		.def("FindComboUI", &PyUIBaseWrap::FindComboUI, return_value_policy<reference_existing_object>())
		.def("FindCheckBoxUI", &PyUIBaseWrap::FindCheckBoxUI, return_value_policy<reference_existing_object>())
		.def("FindProgressUI", &PyUIBaseWrap::FindProgressUI, return_value_policy<reference_existing_object>())
		.def("FindTextUI", &PyUIBaseWrap::FindTextUI, return_value_policy<reference_existing_object>())
		.def("FindEditUI", &PyUIBaseWrap::FindEditUI, return_value_policy<reference_existing_object>())
		.def("FindRichEditUI", &PyUIBaseWrap::FindRichEditUI, return_value_policy<reference_existing_object>())
		.def("FindAnimationUI", &PyUIBaseWrap::FindAnimationUI, return_value_policy<reference_existing_object>())
		.def("FindContainerUI", &PyUIBaseWrap::FindContainerUI, return_value_policy<reference_existing_object>())
		.def("FindTabLayoutUI", &PyUIBaseWrap::FindTabLayoutUI, return_value_policy<reference_existing_object>())
		.def("FindHorizontalLayoutUI", &PyUIBaseWrap::FindHorizontalLayoutUI, return_value_policy<reference_existing_object>())
		.def("FindVerticalLayoutUI", &PyUIBaseWrap::FindVerticalLayoutUI, return_value_policy<reference_existing_object>())
		.def("FindListUI", &PyUIBaseWrap::FindListUI, return_value_policy<reference_existing_object>())
		.def("FindListContainerElementUI", &PyUIBaseWrap::FindListContainerElementUI, return_value_policy<reference_existing_object>())
		.def("FindWebBrowserUI", &PyUIBaseWrap::FindWebBrowserUI, return_value_policy<reference_existing_object>())

		// 业务类
		.def("GetWindowClassName", &PyUIBaseWrap::GetWindowClassName, &PyUIBaseWrap::default_GetWindowClassName)
		// 消息处理
		.def("OnFinalMessage", &PyUIBaseWrap::OnFinalMessage, &PyUIBaseWrap::default_OnFinalMessage)
		.def("InitWindow", &PyUIBaseWrap::InitWindow, &PyUIBaseWrap::default_InitWindow)
		.def("HandleMessage", &PyUIBaseWrap::HandleMessage, &PyUIBaseWrap::default_HandleMessage)
		.def("HandleCustomMessage", &PyUIBaseWrap::HandleCustomMessage, &PyUIBaseWrap::default_HandleCustomMessage)
		.def("OnNotify", &PyUIBaseWrap::OnNotify, &PyUIBaseWrap::default_OnNotify)
		.def("OnPrepare", &PyUIBaseWrap::OnPrepare, &PyUIBaseWrap::default_OnPrepare)
		.def("OnExit", &PyUIBaseWrap::OnExit, &PyUIBaseWrap::default_OnExit)
		.def("OnTimer", &PyUIBaseWrap::OnTimer, &PyUIBaseWrap::default_OnTimer)
		;

	class_<PyLog>("PyLog")
		.def("LogText", &PyLog::LogText)
		. staticmethod("LogText") 
		;

	class_<PyTest>("PyTest")
		.def("Test", &PyTest::Test)
		;

	class_<PyScript>("PyScript")
		.def("RunPy", &PyScript::RunPy)
		;

	class_<CWin32Api>("PyWinUtils")
		.def("GetExeDirectory", &CWin32Api::GetExeDirectory)
		.def("SetCurrentDirectory", &CWin32Api::SetCurrentDirectory)
		.def("SetCurrentDirectoryToExePath", &CWin32Api::SetCurrentDirectoryToExePath)
		.def("SetWaitCursor", &CWin32Api::SetWaitCursor)
		.def("SetArrowCursor", &CWin32Api::SetArrowCursor)
		.def("ShellExcute", &CWin32Api::ShellExcute)
		.def("SelectFile", &CWin32Api::SelectFile)
		.def("MessageBox", &CWin32Api::MessageBox)
		.def("SelectFolder", &CWin32Api::SelectFolder)
		.def("CreateDirectory", &CWin32Api::CreateDirectory)
		.def("Sleep", &CWin32Api::Sleep)
		.def("SetTimer", &CWin32Api::SetTimer)
		.def("KillTimer", &CWin32Api::KillTimer)
		.def("SetConnectionOptions", &CWin32Api::SetConnectionOptions)
		.def("DisableConnectionProxy", &CWin32Api::DisableConnectionProxy)
		;

	class_<PyFrameCreator>("PyFrameCreator")
		.def("CreateWindow", &PyFrameCreator::PyCreateWindow)
		.def("CreateForm", &PyFrameCreator::PyCreateForm)
		.def("CreateDialog", &PyFrameCreator::PyCreateDialog)
		.def("ShowModal", &PyFrameCreator::ShowModal)
		.def("Show", &PyFrameCreator::Show)
		; 

	register_ptr_to_python <PyFrame_ptr>();  
	register_ptr_to_python <PyControlUI_ptr>();  
	register_ptr_to_python <PyLabelUI_ptr>();  
	register_ptr_to_python <PyButtonUI_ptr>();  
	register_ptr_to_python <PyOptionUI_ptr>();  
	register_ptr_to_python <PyCheckBoxUI_ptr>();  
	register_ptr_to_python <PyProgressUI_ptr>();  
	register_ptr_to_python <PyAnimationUI_ptr>();  
	register_ptr_to_python <PyHorizontalLayoutUI_ptr>();  
	register_ptr_to_python <PyVerticalLayoutUI_ptr>();  
	register_ptr_to_python <PyTabLayoutUI_ptr>();  
	register_ptr_to_python <PyListUI_ptr>();  
	register_ptr_to_python <PyListContainerElementUI_ptr>();  
	register_ptr_to_python <PyUIFactory_ptr>();  
}

void PyExtentInit()
{
	duilib_registration();
	PyImport_AppendInittab("PyUI", initPyUI);
}

std::string PyScript::RunPy(std::string pyModule, std::string pyFunc)
{
	std::string ret = "";

	boost::python::handle<>* _module = NULL; // Module handle.

	try
	{
		_module = new boost::python::handle<>(
			PyImport_ImportModule( pyModule.c_str()));
		ret = boost::python::call_method<std::string>(_module->get(), pyFunc.c_str());
	}
	catch(boost::python::error_already_set const &){  
		ret = parse_python_exception();
		PyLog().LogText(ret.c_str());
		PyErr_Clear();
	}  
	catch (...)
	{
		if (PyErr_Occurred())
		{
			ret = parse_python_exception();
			PyLog().LogText(ret.c_str());
			PyErr_Clear();
		}
	}

	if (_module)
		delete _module;

	return ret;
}
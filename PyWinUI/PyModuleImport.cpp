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
typedef boost::shared_ptr < PyControlUI > PyControlUI_ptr;  
typedef boost::shared_ptr < PyLabelUI > PyLabelUI_ptr;  
typedef boost::shared_ptr < PyButtonUI > PyButtonUI_ptr;  
typedef boost::shared_ptr < PyOptionUI > PyOptionUI_ptr;  
typedef boost::shared_ptr < PyCheckBoxUI > PyCheckBoxUI_ptr;  
typedef boost::shared_ptr < PyProgressUI > PyProgressUI_ptr;  
typedef boost::shared_ptr < PyAnimationUI > PyAnimationUI_ptr;  
typedef boost::shared_ptr < PyHorizontalLayoutUI > PyHorizontalLayoutUI_ptr;  
typedef boost::shared_ptr < PyVerticalLayoutUI > PyVerticalLayoutUI_ptr;  
typedef boost::shared_ptr < PyTabLayoutUI > PyTabLayoutUI_ptr;  
typedef boost::shared_ptr < PyListUI > PyListUI_ptr;  
typedef boost::shared_ptr < PyListContainerElementUI > PyListContainerElementUI_ptr;  
typedef boost::shared_ptr < PyUIFactory > PyUIFactory_ptr;  

BOOST_PYTHON_MODULE(PyUI)
{
	class_<CControlUI, boost::noncopyable>("CControlUI")
		.def("SetName", &CControlUI::SetName)
		.def("ApplyAttributeList", &CControlUI::ApplyAttributeList, return_value_policy<reference_existing_object>())
		.def("SetText", &CControlUI::SetText)
		.def("GetText", &CControlUI::GetText)
		.def("IsVisible", &CControlUI::IsVisible)
		.def("SetVisible", &CControlUI::SetVisible)
		.def("IsEnabled", &CControlUI::IsEnabled)
		.def("SetEnabled", &CControlUI::SetEnabled)
		.def("IsFocused", &CControlUI::IsFocused)
		.def("SetFocus", &CControlUI::SetFocus)
		; 

	class_<PyControlUI>("PyControlUI", init<PControlUI>())
		.def("SetName", &PyControlUI::SetName)
		.def("GetSelf", &PyControlUI::GetSelf)
		.def("ApplyAttributeList", &PyControlUI::ApplyAttributeList)
		.def("SetText", &PyControlUI::SetText)
		.def("GetText", &PyControlUI::GetText)
		.def("IsVisible", &PyControlUI::IsVisible)
		.def("SetVisible", &PyControlUI::SetVisible)
		.def("IsEnabled", &PyControlUI::IsEnabled)
		.def("SetEnabled", &PyControlUI::SetEnabled)
		.def("IsFocused", &PyControlUI::IsFocused)
		.def("SetFocus", &PyControlUI::SetFocus)
		; 

	class_<PyLabelUI>("PyLabelUI", init<PControlUI>())
		.def("SetName", &PyLabelUI::SetName)
		.def("GetSelf", &PyLabelUI::GetSelf)
		.def("ApplyAttributeList", &PyLabelUI::ApplyAttributeList)
		.def("SetText", &PyLabelUI::SetText)
		.def("GetText", &PyLabelUI::GetText)
		.def("IsVisible", &PyLabelUI::IsVisible)
		.def("SetVisible", &PyLabelUI::SetVisible)
		.def("IsEnabled", &PyLabelUI::IsEnabled)
		.def("SetEnabled", &PyLabelUI::SetEnabled)
		.def("IsFocused", &PyLabelUI::IsFocused)
		.def("SetFocus", &PyLabelUI::SetFocus)
		; 

	class_<PyButtonUI>("PyButtonUI", init<PControlUI>())
		.def("SetName", &PyButtonUI::SetName)
		.def("GetSelf", &PyButtonUI::GetSelf)
		.def("ApplyAttributeList", &PyButtonUI::ApplyAttributeList)
		.def("SetText", &PyButtonUI::SetText)
		.def("GetText", &PyButtonUI::GetText)
		.def("IsVisible", &PyButtonUI::IsVisible)
		.def("SetVisible", &PyButtonUI::SetVisible)
		.def("IsEnabled", &PyButtonUI::IsEnabled)
		.def("SetEnabled", &PyButtonUI::SetEnabled)
		.def("IsFocused", &PyButtonUI::IsFocused)
		.def("SetFocus", &PyButtonUI::SetFocus)
		; 

	class_<PyOptionUI>("PyOptionUI", init<PControlUI>())
		.def("SetName", &PyOptionUI::SetName)
		.def("GetSelf", &PyOptionUI::GetSelf)
		.def("ApplyAttributeList", &PyOptionUI::ApplyAttributeList)
		.def("IsVisible", &PyOptionUI::IsVisible)
		.def("SetVisible", &PyOptionUI::SetVisible)
		.def("IsEnabled", &PyOptionUI::IsEnabled)
		.def("SetEnabled", &PyOptionUI::SetEnabled)
		; 

	class_<PyCheckBoxUI>("PyCheckBoxUI", init<PControlUI>())
		.def("SetName", &PyCheckBoxUI::SetName)
		.def("GetSelf", &PyCheckBoxUI::GetSelf)
		.def("ApplyAttributeList", &PyCheckBoxUI::ApplyAttributeList)
		.def("SetCheck", &PyCheckBoxUI::SetCheck)
		.def("GetCheck", &PyCheckBoxUI::GetCheck)
		.def("IsVisible", &PyCheckBoxUI::IsVisible)
		.def("SetVisible", &PyCheckBoxUI::SetVisible)
		.def("IsEnabled", &PyCheckBoxUI::IsEnabled)
		.def("SetEnabled", &PyCheckBoxUI::SetEnabled)
		; 

	class_<PyProgressUI>("PyProgressUI", init<PControlUI>())
		.def("SetName", &PyProgressUI::SetName)
		.def("GetSelf", &PyProgressUI::GetSelf)
		.def("ApplyAttributeList", &PyProgressUI::ApplyAttributeList)
		.def("SetValue", &PyProgressUI::SetValue)
		.def("GetValue", &PyProgressUI::GetValue)
		.def("IsVisible", &PyProgressUI::IsVisible)
		.def("SetVisible", &PyProgressUI::SetVisible)
		.def("IsEnabled", &PyProgressUI::IsEnabled)
		.def("SetEnabled", &PyProgressUI::SetEnabled)
		; 

	class_<PyAnimationUI>("PyAnimationUI", init<PControlUI>())
		.def("SetName", &PyAnimationUI::SetName)
		.def("GetSelf", &PyAnimationUI::GetSelf)
		.def("ApplyAttributeList", &PyAnimationUI::ApplyAttributeList)
		.def("IsVisible", &PyAnimationUI::IsVisible)
		.def("SetVisible", &PyAnimationUI::SetVisible)
		.def("IsEnabled", &PyAnimationUI::IsEnabled)
		.def("SetEnabled", &PyAnimationUI::SetEnabled)
		.def("StopAnimation", &PyAnimationUI::StopAnimation)
		.def("StartAnimation", &PyAnimationUI::StartAnimation)
		; 

	class_<PyHorizontalLayoutUI>("PyHorizontalLayoutUI", init<PControlUI>())
		.def("SetName", &PyHorizontalLayoutUI::SetName)
		.def("GetSelf", &PyHorizontalLayoutUI::GetSelf)
		.def("ApplyAttributeList", &PyHorizontalLayoutUI::ApplyAttributeList)
		.def("SetAttribute", &PyHorizontalLayoutUI::SetAttribute)
		.def("IsVisible", &PyHorizontalLayoutUI::IsVisible)
		.def("SetVisible", &PyHorizontalLayoutUI::SetVisible)
		.def("IsEnabled", &PyHorizontalLayoutUI::IsEnabled)
		.def("SetEnabled", &PyHorizontalLayoutUI::SetEnabled)
		.def("Add", &PyHorizontalLayoutUI::Add)
		; 

	class_<PyVerticalLayoutUI>("PyVerticalLayoutUI", init<PControlUI>())
		.def("SetName", &PyVerticalLayoutUI::SetName)
		.def("GetSelf", &PyVerticalLayoutUI::GetSelf)
		.def("ApplyAttributeList", &PyVerticalLayoutUI::ApplyAttributeList)
		.def("SetAttribute", &PyVerticalLayoutUI::SetAttribute)
		.def("IsVisible", &PyVerticalLayoutUI::IsVisible)
		.def("SetVisible", &PyVerticalLayoutUI::SetVisible)
		.def("IsEnabled", &PyVerticalLayoutUI::IsEnabled)
		.def("SetEnabled", &PyVerticalLayoutUI::SetEnabled)
		.def("Add", &PyVerticalLayoutUI::Add)
		; 

	class_<PyTabLayoutUI>("PyTabLayoutUI", init<PControlUI>())
		.def("SetName", &PyTabLayoutUI::SetName)
		.def("GetSelf", &PyTabLayoutUI::GetSelf)
		.def("ApplyAttributeList", &PyTabLayoutUI::ApplyAttributeList)
		.def("SetText", &PyTabLayoutUI::SetText)
		.def("GetText", &PyTabLayoutUI::GetText)
		.def("IsVisible", &PyTabLayoutUI::IsVisible)
		.def("SetVisible", &PyTabLayoutUI::SetVisible)
		.def("IsEnabled", &PyTabLayoutUI::IsEnabled)
		.def("SetEnabled", &PyTabLayoutUI::SetEnabled)
		.def("IsFocused", &PyTabLayoutUI::IsFocused)
		.def("SetFocus", &PyTabLayoutUI::SetFocus)
		.def("SelectItem", &PyTabLayoutUI::SelectItem)
		.def("Add", &PyTabLayoutUI::Add)
		; 

	class_<PyListUI>("PyListUI", init<PControlUI>())
		.def("SetName", &PyListUI::SetName)
		.def("GetSelf", &PyListUI::GetSelf)
		.def("ApplyAttributeList", &PyListUI::ApplyAttributeList)
		.def("IsVisible", &PyListUI::IsVisible)
		.def("SetVisible", &PyListUI::SetVisible)
		.def("IsEnabled", &PyListUI::IsEnabled)
		.def("SetEnabled", &PyListUI::SetEnabled)
		.def("Add", &PyListUI::Add)
		; 

	class_<PyListContainerElementUI>("PyListContainerElementUI", init<PControlUI>())
		.def("SetName", &PyListContainerElementUI::SetName)
		.def("GetSelf", &PyListContainerElementUI::GetSelf)
		.def("ApplyAttributeList", &PyListContainerElementUI::ApplyAttributeList)
		.def("IsVisible", &PyListContainerElementUI::IsVisible)
		.def("SetVisible", &PyListContainerElementUI::SetVisible)
		.def("IsEnabled", &PyListContainerElementUI::IsEnabled)
		.def("SetEnabled", &PyListContainerElementUI::SetEnabled)
		.def("Add", &PyListContainerElementUI::Add)
		; 

	class_<PyUIFactory>("PyUIFactory")
		.def("CreateControlUI", &PyUIFactory::CreateControlUI)
		.def("CreateLabelUI", &PyUIFactory::CreateLabelUI)
		.def("CreateButtonUI", &PyUIFactory::CreateButtonUI)
		.def("CreateOptionUI", &PyUIFactory::CreateOptionUI)
		.def("CreateCheckBoxUI", &PyUIFactory::CreateCheckBoxUI)
		.def("CreateProgressUI", &PyUIFactory::CreateProgressUI)
		.def("CreateAnimationUI", &PyUIFactory::CreateAnimationUI)
		.def("CreateHorizontalLayoutUI", &PyUIFactory::CreateHorizontalLayoutUI)
		.def("CreateVerticalLayoutUI", &PyUIFactory::CreateVerticalLayoutUI)
		.def("CreateTabLayoutUI", &PyUIFactory::CreateTabLayoutUI)
		.def("CreateListUI", &PyUIFactory::CreateListUI)
		.def("CreateListContainerElementUI", &PyUIFactory::CreateListContainerElementUI)
		; 

	//class_<PyUIBase, boost::noncopyable>("PyFrame")
	//	.def("SetHWnd", &PyUIBase::SetHWnd)
	//	.def("GetHWnd", &PyUIBase::GetHWnd)
	//	.def("SetCaption", &PyUIBase::SetCaption)
	//	.def("CloseWindow", &PyUIBase::CloseWindow)
	//	.def("HideWindow", &PyUIBase::HideWindow)
	//	.def("ExitApp", &PyUIBase::ExitApp)	

	//	//.def("Show", &PyUIBase::Show)
	//	//.def("ShowModal", &PyUIBase::ShowModal)

	//	.def("GetSkinFile", &PyUIBase::GetSkinFile)
	//	.def("GetWindowClassName", &PyUIBase::GetWindowClassName)
	//	.def("OnFinalMessage", &PyUIBase::OnFinalMessage)
	//	.def("InitWindow", &PyUIBase::InitWindow)
	//	.def("HandleMessage", &PyUIBase::HandleMessage)
	//	.def("HandleCustomMessage", &PyUIBase::HandleCustomMessage)
	//	.def("OnNotify", &PyUIBase::OnNotify)
	//	.def("OnPrepare", &PyUIBase::OnPrepare)
	//	.def("OnExit", &PyUIBase::OnExit)
	//	.def("OnTimer", &PyUIBase::OnTimer)
	//	;

	class_<PyUIBaseWrap, boost::noncopyable>("PyUIBase")
		// 方便使用的通用函数
		.def("SetHWnd", &PyUIBaseWrap::SetHWnd)
		.def("GetHWnd", &PyUIBaseWrap::GetHWnd)
		.def("CloseWindow", &PyUIBaseWrap::CloseWindow)
		.def("HideWindow", &PyUIBaseWrap::HideWindow)
		//.def("SetHWnd", &PyUIBaseWrap::SetHWnd, &PyUIBaseWrap::default_SetHWnd)
		//.def("GetHWnd", &PyUIBaseWrap::GetHWnd, &PyUIBaseWrap::default_GetHWnd)
		//.def("SetCaption", &PyUIBaseWrap::SetCaption, &PyUIBaseWrap::default_SetCaption)
		//.def("CloseWindow", &PyUIBaseWrap::CloseWindow, &PyUIBaseWrap::default_CloseWindow)
		//.def("HideWindow", &PyUIBaseWrap::HideWindow, &PyUIBaseWrap::default_HideWindow)
		.def("ExitApp", &PyUIBaseWrap::ExitApp, &PyUIBaseWrap::default_ExitApp)	
		.def("ProcessMessages", &PyUIBaseWrap::ProcessMessages)
		//.def("Show", &PyUIBaseWrap::Show, &PyUIBaseWrap::default_Show)
		//.def("ShowModal", &PyUIBaseWrap::ShowModal, &PyUIBaseWrap::default_ShowModal)

		// 界面皮肤
		.def("GetSkinFile", &PyUIBaseWrap::GetSkinFile, &PyUIBaseWrap::default_GetSkinFile)
		// 界面显示
		.def("SetText", &PyUIBaseWrap::SetText)
		.def("FindControl", &PyUIBaseWrap::FindControl)
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
		;

	class_<PyFrameCreator>("PyFrameCreator")
		.def("CreateForm", &PyFrameCreator::CreateForm)
		//.def("Show", &PyFrameCreator::Show)
		.def("ShowModal", &PyFrameCreator::ShowModal)
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
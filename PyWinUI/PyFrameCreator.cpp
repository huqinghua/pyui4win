
#include "stdafx.h"
#include <windows.h>
#include <shellapi.h>

#include "resource.h"
#include "PyFrameCreator.hpp"
#include "PyFrameUI.hpp"
#include<boost/python.hpp>


PyFrameCreator::PyFrameCreator() : m_pyFrameUI(NULL)
{
}

PyFrameCreator::~PyFrameCreator()
{
}

object PyFrameCreator::CreateForm(ULONG hParent, LPCSTR pyModule, LPCSTR pyClassName)
{
	m_pyModule = pyModule;
	m_pyClassName = pyClassName;

	m_Module = import(pyModule);
	object global(m_Module.attr("__dict__"));
	m_ClassUI = global[pyClassName];
	m_InstanceUI = m_ClassUI();
	m_pyBaseUI = extract<PyUIBase*>(m_InstanceUI) BOOST_EXTRACT_WORKAROUND;

	m_xmlSkinFile = CA2T(m_pyBaseUI->GetSkinFile());
	if (!m_pyFrameUI)
		m_pyFrameUI = new PyFrameUI();
	if( m_pyFrameUI == NULL ) 
		return m_InstanceUI;

	m_pyFrameUI->SetPyBaseUI(m_pyBaseUI);
	HWND hWnd = m_pyFrameUI->Create((HWND)hParent, _T("Python界面开发示例"), UI_WNDSTYLE_DIALOG, 0, 0, 0, 0, 0, NULL);
	m_pyBaseUI->SetHWnd((ULONG)hWnd);
	m_pyBaseUI->SetPyFrameUI(m_pyFrameUI);

	return m_InstanceUI;
}

void PyFrameCreator::Show()
{
	m_pyFrameUI->CenterWindow();
	m_pyFrameUI->ShowWindow(true);	
}

UINT PyFrameCreator::ShowModal()
{
	m_pyFrameUI->CenterWindow();
	return m_pyFrameUI->ShowModal();
}
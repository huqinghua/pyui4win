// Launcher.cpp : main source file for Launcher.exe
//


#include "stdafx.h"
#include <exdisp.h>
#include <comdef.h>
#include <string>
#include <shellapi.h>
#include <shellapi.h>
#include "PyException.h"

#ifdef _DEBUG
#undef _DEBUG
#include <Python.h>
#define _DEBUG
#else
#include <Python.h>
#endif

#include<boost/python.hpp>
using namespace boost::python;

__declspec(selectany) TCHAR g_szExePath[MAX_PATH + 1] = {0};
inline LPCTSTR GetExePath()
{
	if (!g_szExePath[0])
		::GetModuleFileName(NULL, g_szExePath, MAX_PATH);

	return g_szExePath;
}

__declspec(selectany) TCHAR g_szExeFolder[MAX_PATH + 1] = {0};
inline LPCTSTR GetExeFolder()
{
	if (!g_szExeFolder[0])
	{
		memcpy(g_szExeFolder, GetExePath(), MAX_PATH);
		::PathRemoveFileSpec(g_szExeFolder);
	}
	return g_szExeFolder;
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int nCmdShow)
{
    HRESULT Hr = ::CoInitialize(NULL);
    if( FAILED(Hr) )
        return 0;

	// 初始化python
	Py_Initialize();

	PyEval_InitThreads();

	// 将当前目录加入python环境变量
	CString pathA = GetExeFolder();
	//pathA.Replace('\\', '/');
	try
	{
		PyRun_SimpleString("import sys");
		PyRun_SimpleString(
			(std::string("if not '") + (LPCSTR)pathA + "' in sys.path: \n"
			"    sys.path.append('" + (LPCSTR)pathA + "')\n").c_str());
		PyRun_SimpleString(
			(std::string("if not '") + (LPCSTR)pathA + "\\PyModule' in sys.path: \n"
			"    sys.path.append('" + (LPCSTR)pathA + "\\PyModule')\n").c_str());
	}
	catch(boost::python::error_already_set const &)
	{  
		std::string err = parse_python_exception();
		PyErr_Clear();
	}  
	catch (...)
	{
		if (PyErr_Occurred())
		{
			std::string err = parse_python_exception();
			PyErr_Clear();
		}
	}

	// 调用PyMain模块的PyAppInit, 该函数是程序入口
	boost::python::handle<>* _module = NULL; // Module handle.
	try
	{
		_module = new boost::python::handle<>(
			PyImport_ImportModule("AppLaunch"));
		bool ret = boost::python::call_method<bool>(_module->get(), "PyAppLaunch");
		//CPaintManagerUI::MessageLoop();
	}
	catch(boost::python::error_already_set const &)
	{  
		std::string err = parse_python_exception();
		PyErr_Clear();
	}  
	catch (...)
	{
		if (PyErr_Occurred())
		{
			std::string err = parse_python_exception();
			PyErr_Clear();
		}
	}

	if (_module)
		delete _module;

	// Boost.Python doesn't support Py_Finalize yet, so don't call it!

    ::CoUninitialize();
    return 0;
}


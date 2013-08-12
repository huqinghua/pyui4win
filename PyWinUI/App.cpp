// App.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include <exdisp.h>
#include <comdef.h>
#include <string>
#include "WinSys.h"
#include <shellapi.h>
#include "Util.h"
#include "MDbgHelper.h"
#include <shellapi.h>
#include <CommDlg.h>
#include "PyException.h"

#ifdef _DEBUG
#undef _DEBUG
#include <Python.h>
#define _DEBUG
#else
#include <Python.h>
#endif

#include<boost/python.hpp>
#include "PyFrameCreator.hpp"
#include "PyModuleImport.h"
using namespace boost::python;

extern "C" void SwitchToOtherPythonTread()
{
	static boost::python::handle<>* _module = NULL; // Module handle.
	try
	{
		if (!_module)
		{
			_module = new boost::python::handle<>(
				PyImport_ImportModule("PyFrameBase"));
		}
		bool ret = boost::python::call_method<bool>(_module->get(), "GiveUp");
	}
	catch(boost::python::error_already_set const &)
	{  
		std::string err = parse_python_exception();
		PyLog().LogText(err.c_str());
		PyErr_Clear();
	}  
	catch (...)
	{
		if (PyErr_Occurred())
		{
			std::string err = parse_python_exception();
			PyLog().LogText(err.c_str());
			PyErr_Clear();
		}
	}
}

#ifndef XN_PYTHON_EXTEND

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int nCmdShow)
{
	CMDbgHelper::Instance()->SetFilter(MiniDumpWithHandleData | MiniDumpFilterModulePaths | MiniDumpWithThreadInfo);	

    CPaintManagerUI::SetInstance(hInstance);
    //CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath() + _T("skin"));

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
/*		PyRun_SimpleString((std::string("if not '") + (LPCSTR)pathA + "\\DLLs' in sys.path: \n"
			"    sys.path.append('" + (LPCSTR)pathA + "\\DLLs')    \n").c_str()
			);
		PyRun_SimpleString("import sys");
		PyRun_SimpleString(
			(std::string("if not '") + (LPCSTR)pathA + "\\Python27' in sys.path: \n"
			"    sys.path.append('" + (LPCSTR)pathA + "\\Python27')    \n").c_str());
		PyRun_SimpleString(
			"import pywintypes    \n"
			"    pywintypes.__import_pywin32_system_module__(\"pythoncom\", globals())         \n"
			);

		PyRun_SimpleString(
			(std::string("if not '") + (LPCSTR)pathA + "\\Python27\\win32' in sys.path: \n"
			"    sys.path.append('" + (LPCSTR)pathA + "\\Python27\\win32')    \n").c_str());
		PyRun_SimpleString(
			(std::string("if not '") + (LPCSTR)pathA + "\\Python27\\win32com' in sys.path: \n"
			"    sys.path.append('" + (LPCSTR)pathA + "\\Python27\\win32com')    \n").c_str());
		PyRun_SimpleString(
			(std::string("if not '") + (LPCSTR)pathA + "\\Python27\\win32comext' in sys.path: \n"
			"    sys.path.append('" + (LPCSTR)pathA + "\\Python27\\win32comext')    \n").c_str());
*/
		//PyRun_SimpleString((std::string("if not '") + (LPCSTR)pathA + "\\DLLs' in sys.path: \n"
		//	"    sys.path.append('" + (LPCSTR)pathA + "\\DLLs')    \n").c_str()
		//	);
	}
	catch(boost::python::error_already_set const &)
	{  
		std::string err = parse_python_exception();
		PyLog().LogText(err.c_str());
		PyErr_Clear();
	}  
	catch (...)
	{
		if (PyErr_Occurred())
		{
			std::string err = parse_python_exception();
			PyLog().LogText(err.c_str());
			PyErr_Clear();
		}
	}

	// 注册Py模块
	PyExtentInit();

	// 调用PyMain模块的PyAppInit, 该函数是程序入口
	boost::python::handle<>* _module = NULL; // Module handle.
	try
	{
		_module = new boost::python::handle<>(
			PyImport_ImportModule("PyMain"));
		bool ret = boost::python::call_method<bool>(_module->get(), "PyAppInit");
		//CPaintManagerUI::MessageLoop();
	}
	catch(boost::python::error_already_set const &)
	{  
		std::string err = parse_python_exception();
		PyLog().LogText(err.c_str());
		PyErr_Clear();
	}  
	catch (...)
	{
		if (PyErr_Occurred())
		{
			std::string err = parse_python_exception();
			PyLog().LogText(err.c_str());
			PyErr_Clear();
		}
	}

	if (_module)
		delete _module;

	// Boost.Python doesn't support Py_Finalize yet, so don't call it!

    ::CoUninitialize();
    return 0;
}

#else

HINSTANCE g_hInstance;

static int RunDui(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int nCmdShow)
{
	CMDbgHelper::Instance()->SetFilter(MiniDumpWithHandleData | MiniDumpFilterModulePaths | MiniDumpWithThreadInfo);	

	CPaintManagerUI::SetInstance(hInstance);
	//CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath() + _T("skin"));

	HRESULT Hr = ::CoInitialize(NULL);
	if( FAILED(Hr) )
		return 0;

	// 初始化python
	Py_Initialize();

	
	// 将当前目录加入python环境变量
	CString pathA = GetExeFolder();
	//pathA.Replace('\\', '/');
	try
	{
/*
		PyRun_SimpleString("import sys");
		PyRun_SimpleString(
			(std::string("if not '") + (LPCSTR)pathA + "\\Python27' in sys.path: \n"
			"    sys.path.append('" + (LPCSTR)pathA + "\\Python27')    \n").c_str());
		PyRun_SimpleString((std::string("if not '") + (LPCSTR)pathA + "\\DLLs' in sys.path: \n"
			"    sys.path.append('" + (LPCSTR)pathA + "\\DLLs')    \n").c_str()
			);
		PyRun_SimpleString("import sys");
		PyRun_SimpleString(
			(std::string("if not '") + (LPCSTR)pathA + "\\Python27' in sys.path: \n"
			"    sys.path.append('" + (LPCSTR)pathA + "\\Python27')    \n").c_str());
		PyRun_SimpleString(
			"import pywintypes    \n"
			"    pywintypes.__import_pywin32_system_module__(\"pythoncom\", globals())         \n"
			);

		PyRun_SimpleString(
			(std::string("if not '") + (LPCSTR)pathA + "\\Python27\\win32' in sys.path: \n"
			"    sys.path.append('" + (LPCSTR)pathA + "\\Python27\\win32')    \n").c_str());
		PyRun_SimpleString(
			(std::string("if not '") + (LPCSTR)pathA + "\\Python27\\win32com' in sys.path: \n"
			"    sys.path.append('" + (LPCSTR)pathA + "\\Python27\\win32com')    \n").c_str());
		PyRun_SimpleString(
			(std::string("if not '") + (LPCSTR)pathA + "\\Python27\\win32comext' in sys.path: \n"
			"    sys.path.append('" + (LPCSTR)pathA + "\\Python27\\win32comext')    \n").c_str());
*/
		//PyRun_SimpleString((std::string("if not '") + (LPCSTR)pathA + "\\DLLs' in sys.path: \n"
		//	"    sys.path.append('" + (LPCSTR)pathA + "\\DLLs')    \n").c_str()
		//	);
	}
	catch(boost::python::error_already_set const &)
	{  
		std::string err = parse_python_exception();
		PyLog().LogText(err.c_str());
		PyErr_Clear();
	}  
	catch (...)
	{
		if (PyErr_Occurred())
		{
			std::string err = parse_python_exception();
			PyLog().LogText(err.c_str());
			PyErr_Clear();
		}
	}

	// 注册Py模块
	PyExtentInit();

	// 调用PyMain模块的PyAppInit, 该函数是程序入口
	boost::python::handle<>* _module = NULL; // Module handle.
	try
	{
		_module = new boost::python::handle<>(
			PyImport_ImportModule("PyMain"));
		bool ret = boost::python::call_method<bool>(_module->get(), "PyAppInit");
		//CPaintManagerUI::MessageLoop();
	}
	catch(boost::python::error_already_set const &)
	{  
		std::string err = parse_python_exception();
		PyLog().LogText(err.c_str());
		PyErr_Clear();
	}  
	catch (...)
	{
		if (PyErr_Occurred())
		{
			std::string err = parse_python_exception();
			PyLog().LogText(err.c_str());
			PyErr_Clear();
		}
	}

	if (_module)
		delete _module;

	// Boost.Python doesn't support Py_Finalize yet, so don't call it!

	::CoUninitialize();
	return 0;
}

static PyObject* Run(PyObject* self, PyObject* args) 
{
	RunDui(g_hInstance, NULL, NULL, 0);
	return Py_None;
}

BOOL APIENTRY DllMain( HMODULE hModule,
					  DWORD  ul_reason_for_call,
					  LPVOID lpReserved
					  )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		{
			g_hInstance = (HINSTANCE)hModule;
			break;
		}
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}


static PyMethodDef DuiMethods[]= 
{
	{"Run",Run,METH_VARARGS, "run dui"},
	{NULL,NULL,0,NULL}   
};

PyMODINIT_FUNC
init_PyDui4Win(void) {
	(void) Py_InitModule("_PyDui4Win",DuiMethods);
}


#endif
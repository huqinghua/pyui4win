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

HMODULE g_hModule = NULL;

extern "C" void SwitchToOtherPythonTread()
{
	Sleep(10);
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


static int RegisterDui4WinModule()
{
	HRESULT Hr = ::CoInitialize(NULL);
	if( FAILED(Hr) )
		return 0;

	// 初始化python
	Py_Initialize();

	// 注册Py模块
	PyExtentInit();

	return 0;
}



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
		::OutputDebugStringA("pydui4win boost python error_already_set 3");
		std::string err = parse_python_exception();
		PyLog().LogText(err.c_str());
		PyErr_Clear();
		
	}  
	catch (...)
	{
		::OutputDebugStringA("pydui4win boost python error_already_set 4");
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


static int Run4CmdWithoutUI(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int nCmdShow)
{
	CMDbgHelper::Instance()->SetFilter(MiniDumpWithHandleData | MiniDumpFilterModulePaths | MiniDumpWithThreadInfo);	

	HRESULT Hr = ::CoInitialize(NULL);
	if( FAILED(Hr) )
		return 0;

	// 初始化python
	Py_Initialize();

	// 注册Py模块
	PyExtentInit();

	// 调用PyMain模块的PyAppInit, 该函数是程序入口
	boost::python::handle<>* _module = NULL; // Module handle.
	try
	{
		_module = new boost::python::handle<>(
			PyImport_ImportModule("PyMain"));
		bool ret = boost::python::call_method<bool>(_module->get(), "PyAppInit4Robot");
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

static PyObject* RegisterDui4Win(PyObject* self, PyObject* args) 
{
	RegisterDui4WinModule();
	return Py_None;
}

static PyObject* Run4Cmd(PyObject* self, PyObject* args) 
{
	Run4CmdWithoutUI(g_hInstance, NULL, NULL, 0);
	return Py_None;
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
	g_hModule = hModule;

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
	{"Run4Cmd",Run4Cmd,METH_VARARGS, "Run4Cmd"},
	{"RegisterDui4Win",RegisterDui4Win,METH_VARARGS, "Register Dui4Win Module"},
	
	{NULL,NULL,0,NULL}   
};

PyMODINIT_FUNC
init_PyDui4Win(void) {
	(void) Py_InitModule("_PyDui4Win",DuiMethods);
}


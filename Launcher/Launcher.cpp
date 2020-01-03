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

__declspec(selectany) TCHAR g_szBuffer[MAX_PATH + 1] = {0};
inline LPCTSTR GetExeFolderFilePath(LPCTSTR pMore, TCHAR *szBuffer = g_szBuffer)
{
	// 注意用默认参数的时候有潜在的多线程问题
	::PathCombine(szBuffer, GetExeFolder(), pMore);
	return szBuffer;
}

void LOGEx1(LPCTSTR lpszFormat, ...)
{
	va_list args;
	va_start(args, lpszFormat);

	HRESULT hr;
	TCHAR szBuffer[5120]={0};	
	hr = StringCchVPrintf(szBuffer, _countof(szBuffer), lpszFormat, args);
	szBuffer[ _countof(szBuffer) - 1 ] = 0;
	va_end(args);

	static int nIndex = 0;
	nIndex++;
	SYSTEMTIME sysToday;
	GetLocalTime(&sysToday);
	CString strTime;
	strTime.Format( _T("%04d-%02d-%02d %02d:%02d:%02d:%04d_%d process %d thread %d")
		, sysToday.wYear
		, sysToday.wMonth
		, sysToday.wDay
		, sysToday.wHour
		, sysToday.wMinute
		, sysToday.wSecond
		, sysToday.wMilliseconds
		, nIndex
		, GetCurrentProcessId()
		, GetCurrentThreadId());

	WritePrivateProfileString(_T("main"),strTime, szBuffer, GetExeFolderFilePath("applog\\applog.ini"));
}

void UploadLog()
{

	SYSTEMTIME st;
	GetLocalTime(&st);

	CString strFileName;
	strFileName.Format(_T("applog\\applog_%02d%02d%02d%02d%02d.ini"), st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);

	char szExeFolder[MAX_PATH + 1] = {0};
	::GetModuleFileName(GetModuleHandle(0), szExeFolder, MAX_PATH);
	::PathRemoveFileSpec(szExeFolder);
	::SetCurrentDirectory(szExeFolder);
			
	if (::MoveFile( GetExeFolderFilePath("applog\\applog.ini"), strFileName ))
	{
		::OutputDebugStringA("MoveFile success");
		HINSTANCE Result = ::ShellExecute(NULL, 
			"open", 
			"BugReport.exe",
			strFileName,
			NULL,
			SW_HIDE );
		if (Result) 
		{
			::OutputDebugStringA("ShellExecute success");
		}
	}
	else
	{
		::OutputDebugStringA("MoveFile fail");
		HINSTANCE Result = ::ShellExecute(NULL, 
			"open", 
			"BugReport.exe",
			GetExeFolderFilePath("applog\\applog.ini"),
			NULL,
			SW_HIDE );
		if (Result) 
		{
			::OutputDebugStringA("ShellExecute success");
		}
	}
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int nCmdShow)
{
    HRESULT Hr = ::CoInitialize(NULL);
    if( FAILED(Hr) )
        return 0;

	// 初始化python
	Py_Initialize();

	PyEval_InitThreads();




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
		LOGEx1(err.c_str());
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

	UploadLog();
	if (_module)
		delete _module;

	// Boost.Python doesn't support Py_Finalize yet, so don't call it!

    ::CoUninitialize();
    return 0;
}



#if !defined(AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_)
#define AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_

#pragma once

#define WIN32_LEAN_AND_MEAN	
#define _CRT_SECURE_NO_DEPRECATE

#include <windows.h>
#include <objbase.h>
#include "resource.h"

#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NON_CONFORMING_SWPRINTFS

#define STRSAFE_NO_DEPRECATE

#define __ENABLE_CSTRING_CLASS__

#define ARRSIZEOF(x) (sizeof(x)/sizeof(x[0]))

#include <atlbase.h>
#include <atlcoll.h>
#include <atlstr.h>
#include <atltypes.h>
#define _WTL_NO_CSTRING
#define _WTL_NO_WTYPES
#include <atlapp.h>
#include <atlwin.h>
#include <shellapi.h>
#include <atldlgs.h>
#include <atlmisc.h>
#include <atlcrack.h>
#include <atlddx.h>
#include <strSafe.h>

#include <atluser.h>

#include "..\DuiLib\UIlib.h"
#include "Util.h"
using namespace DuiLib;
#ifdef _DEBUG
#pragma comment(lib, "..\\Lib\\DuiLib_d.lib")
#else
#pragma comment(lib, "..\\Lib\\DuiLib.lib")
#endif

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__A9DB83DB_A9FD_11D0_BFD1_444553540000__INCLUDED_)

#include "stdafx.h"
#include "LuaExtScript.h"

#pragma warning(disable : 4018)
#pragma warning(disable : 4267)
#pragma warning(disable : 4244)
#pragma warning(disable : 4101)
#pragma warning(disable : 4311)
#pragma warning(disable : 4312)
#pragma warning(disable : 4190)

#pragma comment(lib, "lua51.lib")

#define  FUNC_REG(F1, F2, FUNC)	{ lua_register(gp_LUA, F1, FUNC); lua_register(gp_LUA, F2, FUNC); }

lua_State			*	gp_LUA=NULL;					//LUA¶ÔÏó

extern "C"  BOOL InitilizeScript()
{
	if (gp_LUA)
	{
		return TRUE;
	}

	gp_LUA=lua_open();
	luaopen_base(gp_LUA);
	luaL_openlibs(gp_LUA);

	FUNC_REG("EX_UIMessageBox", "msgbox", EX_UIMessageBox);
	FUNC_REG("EX_Sleep", "sleep", EX_Sleep);	
	FUNC_REG("EX_SHELLOPEN", "shellopen", EX_SHELLOPEN);
	FUNC_REG("EX_OutPutDebugString", "EOutPutDebugString", EX_OutPutDebugString);

	return TRUE;
}

extern "C"  lua_State* GetLUAStatus()
{
	return gp_LUA;
}

extern "C"  void ExitScript()
{
	if (gp_LUA)
	{
		lua_close(gp_LUA);
		gp_LUA = NULL;
	}	
}

void ExecuteConsoleAndWait (TCHAR toto[])
{
	TCHAR cmd[500];

	strcpy(cmd, toto);
	STARTUPINFO StartInfo;
	StartInfo.wShowWindow = SW_MAXIMIZE;
	ZeroMemory(&StartInfo, sizeof(STARTUPINFO));
	StartInfo.cb = sizeof(STARTUPINFO);
	StartInfo.cbReserved2 = NULL;
	StartInfo.lpDesktop = NULL;
	StartInfo.wShowWindow = SW_HIDE;
	StartInfo.dwFlags = STARTF_USESHOWWINDOW;
	PROCESS_INFORMATION processInfo;

	TCHAR path[MAX_PATH];
	::GetModuleFileName(NULL, path, MAX_PATH);
	::PathRemoveFileSpec(path);
	CreateProcess(NULL, cmd, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, path, &StartInfo, &processInfo);

	WaitForSingleObject(processInfo.hProcess, INFINITE);
	CloseHandle(processInfo.hProcess);
	CloseHandle(processInfo.hThread);
}

static int EX_SHELLOPEN( lua_State *L )
{
	if (!(lua_gettop(L) == 1 
		  && lua_isstring(L, 1)))
	{
		return 0;
	}

	::ShellExecuteA(0, "open", lua_tostring(L, 1), 0, 0, SW_SHOWNORMAL);

	return 1;	
}

static int EX_UIMessageBox(lua_State *L)
{
	if (lua_isstring(L, 1) && lua_isstring(L, 2))
	{
		UINT type = MB_OK;
		if (lua_gettop(L) >=3 && lua_isnumber(L, 3))
			type = lua_tonumber(L, 3);
		if (lua_gettop(L) == 4&& lua_isnumber(L, 4))
			type = type|(UINT)lua_tonumber(L, 4);

		lua_pushnumber(L, ::MessageBoxA(NULL, lua_tostring(L, 1), lua_tostring(L, 2), type));

		return 1;
	}
	else
	{
		return 0;
	}
}

static int EX_OutPutDebugString(lua_State *L)
{
	if (!(lua_gettop(L) == 1))
	{
		return 0;
	}

	OutputDebugStringA(lua_tostring(L, 1));
	
	return 1;
}


static int EX_Sleep(lua_State *L)
{
	if ( !(lua_gettop(L) == 1 
		  && lua_isnumber(L, 1)))
	{
		return 0;
	}

	int i = (int)lua_tointeger(L, 1);
	Sleep( i*1000 );

	return 1;
}

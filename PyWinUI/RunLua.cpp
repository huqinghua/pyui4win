#include "stdafx.h"
#include "LuaExtScript.h"
#include "RunLua.h"

CRunLua::CRunLua(void) : m_pLuaBuf(NULL)
{
}

CRunLua::~CRunLua(void)
{
	if (m_pLuaBuf)
	{
		delete m_pLuaBuf;
		m_pLuaBuf = NULL;
	}
}


void CRunLua::ShowLuaError(lua_State*	pLUA)
{
	CStringA errormsg = lua_tostring(pLUA, -1);
}

int CRunLua::Run()
{
	int ret = -1;

	do 
	{
		CStringA patha = "pack";
		if (::PathFileExistsA(patha.GetBuffer()))
		{
			patha.ReleaseBuffer();

			if (!LoadLuaString(patha))
			{
				ATLTRACE("loadlussting failed");
				break;
			}

			if (!InitilizeScript())
			{
				ATLTRACE("InitilizeScript failed");
				break;
			}

			lua_State*	pLUA = GetLUAStatus();
			strcat(m_pLuaBuf, "\n");

			ATLTRACE("begin execute lua file");
			if (luaL_dostring(pLUA, m_pLuaBuf) != 0)
			{
				ShowLuaError(pLUA);
			}
			else
			{
				lua_getglobal(pLUA, "ExcuteRun");
				if (lua_pcall(pLUA, 0, 1, 0) != 0)
				{
					ShowLuaError(pLUA);
				}
				else
				{
					bool sum = (bool)lua_toboolean(pLUA, -1);
					ret = sum;
					lua_pop(pLUA, 1);
				}
			}

			ExitScript();

			break;
		}
		else
		{
			ATLTRACE("lua file not exits");
		}

		break;
	
	} while (FALSE);

	return ret;
}

BOOL CRunLua::LoadLuaString(CStringA fileName)
{
	BOOL ret = TRUE;

	HANDLE hFile = ::CreateFileA(fileName, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,
		OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL );
	if ( hFile == INVALID_HANDLE_VALUE )
		return FALSE;

	DWORD dwFileSize = GetFileSize(hFile, NULL);
	if (m_pLuaBuf)
	{
		delete m_pLuaBuf;
		m_pLuaBuf = NULL;
	}
	m_pLuaBuf = new char[dwFileSize + 1000];
	memset(m_pLuaBuf, 0, dwFileSize + 1000);

	DWORD dwToRead;
	if(!ReadFile(hFile, m_pLuaBuf + strlen(m_pLuaBuf), dwFileSize, &dwToRead, NULL) || dwToRead != dwFileSize)
	{
		ret = FALSE;
	}
	CloseHandle(hFile);

	return ret;
}


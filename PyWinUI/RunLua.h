#pragma once

class CRunLua
{
public:
	CRunLua(void);
	~CRunLua(void);

	void ShowLuaError(lua_State*	pLUA);
	int Run();
	BOOL LoadLuaString(CStringA fileName);
private:
	char*				m_pLuaBuf;
};

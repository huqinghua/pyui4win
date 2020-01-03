#pragma once

//	Headers for use LUA
extern "C" {
    #include "..\include\Lua\lua.h"
    #include "..\include\Lua\lualib.h"
    #include "..\include\Lua\lauxlib.h"
}

//	LUA defines
#define LUA_CHECK_PARAM_NUM(L,n)				if(lua_gettop(L)!=n){	\
												lua_pushstring(L,"incorrect argument"); \
												lua_error(L);\
												return 1;}

#define LUA_CHECK_PARAM_NUM_N(L,min,max)		if(lua_gettop(L)<min||lua_gettop(L)>max){	\
												lua_pushstring(L,"incorrect argument"); \
												lua_error(L);\
												return 1;}

#define LUA_EXT_DEFINE(fucname)					static int fucname(lua_State *L);

extern "C"  BOOL InitilizeScript();
extern "C"  lua_State* GetLUAStatus();
extern "C"  void ExitScript();

LUA_EXT_DEFINE(EX_SHELLOPEN)
LUA_EXT_DEFINE(EX_UIMessageBox)
LUA_EXT_DEFINE(EX_OutPutDebugString)
LUA_EXT_DEFINE(EX_Sleep)


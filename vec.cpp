#include <algorithm>

#include "af_lua_helpers.h"
#include "af_math.h"

extern lua_State *L;

static const char* myClassName = "Vec4";

static int SetValue(lua_State *L)
{
	DumpStack();
	Vec4* p = (Vec4*)luaL_checkudata(L, -2, myClassName);
	p->x = (float)lua_tonumber(L, -1);
	return 0;
}

static int Vec4NewIndex(lua_State *L)
{
	DumpStack();
	Vec4* p = (Vec4*)luaL_checkudata(L, -3, myClassName);
	const char* key = lua_tostring(L, -2);
	const char* val = lua_tostring(L, -1);
	return 0;
}

static int Vec4Index(lua_State *L)
{
	DumpStack();
	Vec4* p = (Vec4*)luaL_checkudata(L, -2, myClassName);
	const char* key = lua_tostring(L, -1);
	if (!memcmp(key, "SetValue", 9)) {
		lua_pushcfunction(L, SetValue);
		return 1;
	} else {
		lua_pushnumber(L, p->x);
		return 1;
	}
}

static int Vec4New(lua_State *L)
{
	DumpStack();
	Vec4* p = (Vec4*)lua_newuserdata(L, sizeof(Vec4));
	DumpStack();
//	luaL_setmetatable(L, myClassName);
	luaL_getmetatable(L, myClassName);
	DumpStack();
	lua_setmetatable(L, -2);
	DumpStack();
	return 1;
}

void BindVec4()
{
	int r = luaL_newmetatable(L, myClassName);
	assert(r);
	DumpStack();
//	lua_pushvalue(L, -1);
//	lua_pushstring(L, myClassName);
//	DumpStack();
//	lua_settable(L, LUA_REGISTRYINDEX);
//	DumpStack();

	lua_pushstring(L, "__index");
	lua_pushcfunction(L, Vec4Index);
	DumpStack();
	lua_settable(L, -3);
	DumpStack();


//	lua_pushstring(L, "__index");
//	lua_pushcfunction(L, IndexObject);
//	DumpStack();
//	lua_settable(L, -3);
//	DumpStack();

	lua_pushstring(L, "__newindex");
	lua_pushcfunction(L, Vec4NewIndex);
	DumpStack();
	lua_settable(L, -3);
	DumpStack();

	lua_pop(L, 1);
	lua_register(L, "Vec4", Vec4New);
}

#include <windows.h>
#include <algorithm>
#include <string.h>

#include "af_lua_helpers.h"

extern lua_State *L;

static const char* myClassName = "RECT";

#define GET_RECT \
	RECT* r = (RECT*)luaL_checkudata(L, 1, myClassName); \
	if (!r) {	\
		return 0;	\
	} \


static int RECTToString(lua_State *L)
{
	char buf[64];
	RECT* r = (RECT*)luaL_checkudata(L, -1, myClassName);
	sprintf_s(buf, sizeof(buf), "(%f, %f, %f, %f)", r->left, r->top, r->right, r->bottom);
	lua_pushstring(L, buf);
	return 1;
}

static int RECTNew(lua_State *L)
{
	int top = lua_gettop(L);
	RECT r;
	r.left = top < 4 ? 0 : (LONG)lua_tointeger(L, -4);
	r.top = top < 3 ? 0 : (LONG)lua_tointeger(L, -3);
	r.right = top < 2 ? 0 : (LONG)lua_tointeger(L, -2);
	r.bottom = top < 1 ? 0 : (LONG)lua_tointeger(L, -1);
	DumpStack();
	RECT* p = (RECT*)lua_newuserdata(L, sizeof(RECT));
	*p = r;
	DumpStack();
	luaL_getmetatable(L, myClassName);
	DumpStack();
	lua_setmetatable(L, -2);
	DumpStack();
	return 1;
}

void BindWin()
{
	DumpStack();
	int r = luaL_newmetatable(L, myClassName);
	assert(r);
	DumpStack();

	lua_pushstring(L, "__index");
	lua_newtable(L);
	static struct luaL_Reg indexMethods[] =
	{
		{ "left", [](lua_State* L) { GET_RECT lua_pushinteger(L, r->left); return 1; } },
		{ "top", [](lua_State* L) { GET_RECT lua_pushinteger(L, r->top); return 1; } },
		{ "right", [](lua_State* L) { GET_RECT lua_pushinteger(L, r->right); return 1; } },
		{ "bottom", [](lua_State* L) { GET_RECT lua_pushinteger(L, r->bottom); return 1; } },
		{ nullptr, nullptr },
	};
	luaL_setfuncs(L, indexMethods, 0);
	DumpStack();

	lua_settable(L, 1);
	DumpStack();

	lua_pop(L, 1);
	lua_register(L, myClassName, RECTNew);
}

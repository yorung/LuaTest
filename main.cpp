#include "af_lua_helpers.h"
#include <windows.h>

lua_State *L;

void BindMyClass();
void BindVec4();
void BindWin();

static void BindNamespace()
{
	static luaL_Reg inNamespaceFuncs[] = {
		{ "MesBox", [](lua_State* L){ MessageBoxA(nullptr, lua_tostring(L, -1), "MesBox in namespace", MB_OK); return 0; } },
		{ nullptr, nullptr },
	};
	aflBindNamespace(L, "myNamespace", inNamespaceFuncs);
}

static void BindGlobalfuncs()
{
	static luaL_Reg globalFuncs[] = {
		{ "MesBox", [](lua_State* L){ MessageBoxA(nullptr, lua_tostring(L, -1), "lambda box", MB_OK); return 0; } },
		{ nullptr, nullptr },
	};
	lua_pushglobaltable(L);
	aflDumpStack();
	luaL_setfuncs(L, globalFuncs, 0);
	lua_pop(L, 1);
	aflDumpStack();
	//	lua_register(L, "MesBox", MesBox);
}

static void StoreGlobalVariables()
{
	aflDumpStack();
	lua_pushglobaltable(L);
	lua_pushstring(L, "SCREEN_WIDTH");
	lua_pushinteger(L, 1000);
	aflDumpStack();
	lua_settable(L, -3);
	aflDumpStack();
	lua_pop(L, 1);
	aflDumpStack();
}

static void StoreVariablesIntoNamespace()
{
	aflDumpStack();
	lua_pushglobaltable(L);
	lua_pushstring(L, "TestNameSpace");
	lua_newtable(L);

	lua_pushstring(L, "Variable100");
	lua_pushinteger(L, 100);
	aflDumpStack();
	lua_settable(L, -3);

	lua_pushstring(L, "Variable200");
	lua_pushinteger(L, 200);
	aflDumpStack();
	lua_settable(L, -3);

	lua_pushstring(L, "Variable300");
	lua_pushinteger(L, 300);
	aflDumpStack();
	lua_settable(L, -3);

	aflDumpStack();
	lua_settable(L, -3);
	lua_pop(L, 1);
	aflDumpStack();
}

static void Bind()
{
	BindGlobalfuncs();
	BindNamespace();
	BindMyClass();
	BindVec4();
	BindWin();
	StoreGlobalVariables();
	StoreVariablesIntoNamespace();
}

int main(int argc, char* argv[])
{
	L = luaL_newstate();
	luaL_openlibs(L);
	Bind();
//	luaL_dostring(L, "Printer()");
	if (luaL_dofile(L, "main.lua")) {
		printf("%s\n", lua_tostring(L, -1));
		lua_pop(L, 1);
	}
	int top = lua_gettop(L);
	if (top > 0) {
		printf("error! stack is not empty\n");
	}
	lua_close(L);
	//new int;
	_CrtDumpMemoryLeaks();
	return 0;
}

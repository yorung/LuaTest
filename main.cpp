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

static void BindGlobal()
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

static void Bind()
{
	BindGlobal();
	BindNamespace();
	BindMyClass();
	BindVec4();
	BindWin();
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

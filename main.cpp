#include "af_lua_helpers.h"
#include <windows.h>

lua_State *L;

void BindMyClass();
void BindVec4();

static void Bind()
{
	static luaL_Reg globalFuncs[] = {
		{ "MesBox", [](lua_State* L){ MessageBoxA(nullptr, lua_tostring(L, -1), "lambda box", MB_OK); return 0; } },
		{ nullptr, nullptr },
	};
	lua_pushglobaltable(L);
	DumpStack();
	luaL_setfuncs(L, globalFuncs, 0);
	lua_pop(L, 1);
	DumpStack();

//	lua_register(L, "MesBox", MesBox);
	BindMyClass();
	BindVec4();
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

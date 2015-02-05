#include "af_lua_helpers.h"

lua_State *L;

void BindMyClass();
void BindVec4();

static int Printer(lua_State *L)
{
	int top = lua_gettop(L);
	const char* name = lua_tostring(L, 1);
	printf("Printer: top=%d message=%s\n", top, name);
	return 0;
}

static int CreatePrinter(lua_State *L)
{
	int top = lua_gettop(L);
	printf("CreatePrinter: top=%d\n", top);
	lua_pushcfunction(L, Printer);
	return 1;
}

static void Bind()
{
	lua_register(L, "CreatePrinter", CreatePrinter);
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

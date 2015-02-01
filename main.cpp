extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

#include <crtdbg.h>
#include <stdlib.h>
#include <stdint.h>

static lua_State *L;

static int Printer(lua_State *L)
{
	int top = lua_gettop(L);
	const char* name = lua_tostring(L, 1);
	printf("Printer: top=%d message=%s\n", top, name);
	return 0;
}

static int CreateObject(lua_State *L)
{
	int top = lua_gettop(L);
	printf("CreateObject: top=%d\n", top);
	int32_t* val = (int32_t*)lua_newuserdata(L, 4);
	*val = rand();
	return 1;
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
//	lua_register(L, "Printer", Printer);
	lua_register(L, "CreateObject", CreateObject);
	lua_register(L, "CreatePrinter", CreatePrinter);
}

int main(int argc, char* argv[])
{
	L = luaL_newstate();
	luaL_openlibs(L);
	Bind();
//	luaL_dostring(L, "Printer()");
	luaL_dofile(L, "main.lua");
	int top = lua_gettop(L);
	if (top > 0) {
		printf("error! stack is not empty\n");
	}
	lua_close(L);
	//new int;
	_CrtDumpMemoryLeaks();
	return 0;
}

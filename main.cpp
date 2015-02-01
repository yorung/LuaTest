extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

static lua_State *L;

static int Printer(lua_State *L)
{
	printf("test\n");
	return 0;
}

static void Bind()
{
	lua_register(L, "Printer", Printer);
}

int main(int argc, char* argv[])
{
	L = luaL_newstate();
	luaL_openlibs(L);
	Bind();
	luaL_dostring(L, "Printer()");

	int top = lua_gettop(L);
	if (top > 0) {
		printf("error! stack is not empty\n");
	}
	lua_close(L);
	return 0;
}

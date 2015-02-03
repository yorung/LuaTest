extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

#include <crtdbg.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>

static lua_State *L;

class MyClass
{
public:
	int dummy;
};

const char* myClassName = "MyClass";

static void _dumpStack(const char* func, int line)
{
	int top = lua_gettop(L);
	printf("(%s,%d) top=%d\n", func, line, top);
	for (int i = 0; i < top; i++) {
		int positive = top - i;
		int negative = -(i + 1);
		int type = lua_type(L, positive);
		int typeN = lua_type(L, negative);
		assert(type == typeN);
		const char* typeName = lua_typename(L, type);
		const char* value = lua_tostring(L, positive);
		const char* valueN = lua_tostring(L, negative);
		printf("%d/%d: type=%s value=%s\n", positive, negative, typeName, value);
	}
}
#define DumpStack() _dumpStack(__FUNCTION__, __LINE__)

static int Printer(lua_State *L)
{
	int top = lua_gettop(L);
	const char* name = lua_tostring(L, 1);
	printf("Printer: top=%d message=%s\n", top, name);
	return 0;
}

static int SetValueObject(lua_State *L)
{
	DumpStack();
	MyClass** pp = (MyClass**)luaL_checkudata(L, -2, myClassName);
	(*pp)->dummy = lua_tointeger(L, -1);
	return 0;
}

static int IndexObject(lua_State *L)
{
	DumpStack();
	MyClass** pp = (MyClass**)luaL_checkudata(L, -2, myClassName);
	const char* key = lua_tostring(L, -1);
	if (!memcmp(key, "SetValue", 9)) {
		lua_pushcfunction(L, SetValueObject);
		return 1;
	} else {
		lua_pushinteger(L, (*pp)->dummy);
		return 1;
	}
}

static int DestroyObject(lua_State *L)
{
	DumpStack();
	MyClass** pp = (MyClass**)luaL_checkudata(L, -1, myClassName);
	delete *pp;
	DumpStack();
	return 0;
}

static int CreateObject(lua_State *L)
{
	DumpStack();
	MyClass** pp = (MyClass**)lua_newuserdata(L, sizeof(MyClass*));
	DumpStack();
	*pp = new MyClass;
	(*pp)->dummy = rand() % 100;
//	luaL_setmetatable(L, myClassName);
	luaL_getmetatable(L, myClassName);
	DumpStack();
	lua_setmetatable(L, -2);
	DumpStack();
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
	int r = luaL_newmetatable(L, myClassName);
	assert(r);
	DumpStack();
	lua_pushvalue(L, -1);
	lua_pushstring(L, myClassName);
	DumpStack();
	lua_settable(L, LUA_REGISTRYINDEX);
	DumpStack();

	lua_pushstring(L, "__gc");
	lua_pushcfunction(L, DestroyObject);
	DumpStack();
	lua_settable(L, -3);
	DumpStack();

	lua_pushstring(L, "__index");
	lua_pushcfunction(L, IndexObject);
	DumpStack();
	lua_settable(L, -3);
	DumpStack();

	lua_pop(L, 1);

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

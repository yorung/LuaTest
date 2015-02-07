#include "af_lua_helpers.h"

extern lua_State *L;


class MyClass
{
public:
	int value;
};

static const char* myClassName = "MyClass";

static int MyClassSetValue(lua_State *L)
{
	DumpStack();
	MyClass** pp = (MyClass**)luaL_checkudata(L, -2, myClassName);
	(*pp)->value = (int)lua_tointeger(L, -1);
	return 0;
}

static int MyClassGetValue(lua_State *L)
{
	DumpStack();
	MyClass** pp = (MyClass**)luaL_checkudata(L, -1, myClassName);
	lua_pushinteger(L, (*pp)->value);
	return 1;
}

static int MyClassGC(lua_State *L)
{
	DumpStack();
	MyClass** pp = (MyClass**)luaL_checkudata(L, -1, myClassName);
	delete *pp;
	DumpStack();
	return 0;
}

static int MyClassNew(lua_State *L)
{
	MyClass** pp = (MyClass**)lua_newuserdata(L, sizeof(MyClass*));
	DumpStack();
	*pp = new MyClass;
	(*pp)->value = 0;
	luaL_getmetatable(L, myClassName);
	DumpStack();
	lua_setmetatable(L, -2);
	DumpStack();
	return 1;
}

void BindMyClass()
{
	int r = luaL_newmetatable(L, myClassName);
	assert(r);
	DumpStack();

	lua_pushstring(L, "__index");
	lua_pushvalue(L, 1);
	DumpStack();
	lua_settable(L, -3);
	DumpStack();

	lua_pushstring(L, "__gc");
	lua_pushcfunction(L, MyClassGC);
	DumpStack();
	lua_settable(L, -3);
	DumpStack();

	lua_pushstring(L, "SetValue");
	lua_pushcfunction(L, MyClassSetValue);
	DumpStack();
	lua_settable(L, -3);
	DumpStack();

	lua_pushstring(L, "GetValue");
	lua_pushcfunction(L, MyClassGetValue);
	DumpStack();
	lua_settable(L, -3);
	DumpStack();

	lua_pop(L, 1);
	lua_register(L, "MyClass", MyClassNew);
}

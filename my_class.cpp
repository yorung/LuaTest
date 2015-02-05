#include "af_lua_helpers.h"

extern lua_State *L;


class MyClass
{
public:
	int dummy;
};

const char* myClassName = "MyClass";

static int SetValue(lua_State *L)
{
	DumpStack();
	MyClass** pp = (MyClass**)luaL_checkudata(L, -2, myClassName);
	(*pp)->dummy = (int)lua_tointeger(L, -1);
	return 0;
}

static int TestMethod(lua_State *L)
{
	DumpStack();
	return 0;
}

static int NewindexObject(lua_State *L)
{
	DumpStack();
	MyClass** pp = (MyClass**)luaL_checkudata(L, -3, myClassName);
	const char* key = lua_tostring(L, -2);
	const char* val = lua_tostring(L, -1);
	return 0;
}

static int IndexObject(lua_State *L)
{
	DumpStack();
	MyClass** pp = (MyClass**)luaL_checkudata(L, -2, myClassName);
	const char* key = lua_tostring(L, -1);
	if (!memcmp(key, "SetValue", 9)) {
		lua_pushcfunction(L, SetValue);
		return 1;
	} else {
		lua_pushinteger(L, (*pp)->dummy);
		return 1;
	}
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

void BindMyClass()
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
	lua_pushvalue(L, 1);
	DumpStack();
	lua_settable(L, -3);
	DumpStack();

	lua_pushstring(L, "__gc");
	lua_pushcfunction(L, MyClassGC);
	DumpStack();
	lua_settable(L, -3);
	DumpStack();

//	lua_pushstring(L, "__index");
//	lua_pushcfunction(L, IndexObject);
//	DumpStack();
//	lua_settable(L, -3);
//	DumpStack();

	lua_pushstring(L, "__newindex");
	lua_pushcfunction(L, NewindexObject);
	DumpStack();
	lua_settable(L, -3);
	DumpStack();

	lua_pushstring(L, "TestMethod");
	lua_pushcfunction(L, TestMethod);
	DumpStack();
	lua_settable(L, -3);
	DumpStack();

	lua_pop(L, 1);
	lua_register(L, "MyClass", MyClassNew);
}

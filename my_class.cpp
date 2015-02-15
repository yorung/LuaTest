#include "af_lua_helpers.h"

#include <new>

extern lua_State *L;


class MyClass
{
public:
	MyClass() { puts("MyClass::MyClass called"); }
	~MyClass() { puts("MyClass::~MyClass called"); }
	int value;
};

namespace
{
	char myClassName[] = "MyClass";
}

#define GET_MYCLASS \
	MyClass* p = (MyClass*)luaL_checkudata(L, 1, myClassName); \
	if (!p) { return 0; }

static int MyClassSetValue(lua_State *L)
{
	GET_MYCLASS
	DumpStack();
	p->value = (int)lua_tointeger(L, -1);
	return 0;
}

static int MyClassGetValue(lua_State *L)
{
	GET_MYCLASS
	DumpStack();
	lua_pushinteger(L, p->value);
	return 1;
}

static int MyClassNew(lua_State *L)
{
	MyClass* p = new (lua_newuserdata(L, sizeof(MyClass))) MyClass;
	DumpStack();
	p->value = 0;
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

	static struct luaL_Reg methods[] =
	{
		{ "__gc", [](lua_State* L) { GET_MYCLASS p->~MyClass(); return 0; } },
		{"SetValue", MyClassSetValue},
		{"GetValue", MyClassGetValue},
		{nullptr, nullptr},
	};
	luaL_setfuncs(L, methods, 0);
	DumpStack();

	lua_pop(L, 1);
	lua_register(L, "MyClass", MyClassNew);
}

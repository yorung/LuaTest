#include "af_lua_helpers.h"

#include <new>

extern lua_State *L;

class MyClass
{
public:
	MyClass()
	{
		value = 0;
		puts("MyClass::MyClass called");
	}
	~MyClass()
	{
		puts("MyClass::~MyClass called");
	}
	int value;
};

static const char* myClassName = "MyClass";

#define GET_MYCLASS \
	MyClass* p = (MyClass*)luaL_checkudata(L, 1, myClassName); \
	if (!p) { return 0; }

void BindMyClass()
{
	static struct luaL_Reg methods[] =
	{
		{ "__gc", [](lua_State* L) { GET_MYCLASS p->~MyClass(); return 0; } },
		{ "SetValue", [](lua_State* L) { GET_MYCLASS p->value = (int)lua_tointeger(L, -1); return 0; } },
		{ "GetValue", [](lua_State* L) { GET_MYCLASS lua_pushinteger(L, p->value); return 1; } },
		{ nullptr, nullptr },
	};
	aflBindClass(L, myClassName, methods, [](lua_State* L) { new (lua_newuserdata(L, sizeof(MyClass))) MyClass; return 1; });
}

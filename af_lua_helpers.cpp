#include "af_lua_helpers.h"

void _dumpStack(lua_State* L, const char* func, int line)
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
		printf("%d/%d: type=%s", positive, negative, typeName);
		switch (type) {
		case LUA_TNUMBER:
			printf(" value=%f", lua_tonumber(L, positive));
			break;
		case LUA_TSTRING:
			printf(" value=%s", lua_tostring(L, positive));
			break;
		}
		printf("\n");
	}
}


static int CreateCppClassInstance(lua_State* L)
{
	DumpStack();
	const char* className = lua_tostring(L, lua_upvalueindex(1));
	lua_CFunction actualInstanceCreator = lua_tocfunction(L, lua_upvalueindex(2));
	actualInstanceCreator(L);
	DumpStack();
	luaL_getmetatable(L, className);
	DumpStack();
	lua_setmetatable(L, -2);
	DumpStack();
	return 1;
}

static void CreateClassMetatable(lua_State* L, const char* className, luaL_Reg methods[])
{
	int r = luaL_newmetatable(L, className);
	assert(r);

	lua_pushstring(L, "__index");
	lua_pushvalue(L, 1);
	lua_settable(L, -3);

	luaL_setfuncs(L, methods, 0);
	lua_pop(L, 1);
}

static void CreateClassInstanceCreator(lua_State* L, const char* className, lua_CFunction creator)
{
	lua_pushstring(L, className);
	lua_pushcfunction(L, creator);
	DumpStack();
	lua_pushcclosure(L, CreateCppClassInstance, 2);
	DumpStack();
	lua_setglobal(L, className);
	DumpStack();
}

void BindClass(lua_State* L, const char* className, luaL_Reg methods[], lua_CFunction creator)
{
	CreateClassMetatable(L, className, methods);
	CreateClassInstanceCreator(L, className, creator);
}

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


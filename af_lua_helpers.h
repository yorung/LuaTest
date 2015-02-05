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

void _dumpStack(lua_State* L, const char* func, int line);
#ifdef _DEBUG
#define DumpStack() _dumpStack(L, __FUNCTION__, __LINE__)
#else
#define DumpStack()
#endif


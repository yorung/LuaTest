#include <lua.hpp>
#include <crtdbg.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>

void _dumpStack(lua_State* L, const char* func, int line);
#ifdef _DEBUG
#define DumpStack() _dumpStack(L, __FUNCTION__, __LINE__)
#define DumpStackL(L) _dumpStack(L, __FUNCTION__, __LINE__)
#else
#define DumpStack()
#define DumpStackL(L)
#endif

void BindClass(lua_State* L, const char* className, luaL_Reg methods[], lua_CFunction creator);

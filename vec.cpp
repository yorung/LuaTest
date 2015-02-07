#include <algorithm>
#include <string.h>

#include "af_lua_helpers.h"
#include "af_math.h"

extern lua_State *L;

static const char* myClassName = "Vec4";

static float& vec4IndexByChar(Vec4& v, char c)
{
	switch (c) {
	case 'x': return v.x;
	case 'y': return v.y;
	case 'z': return v.z;
	case 'w': return v.w;
	}
	static float dummyForSafe;
	return dummyForSafe;
}

static int Vec4ToString(lua_State *L)
{
	char buf[64];
	Vec4* self = (Vec4*)luaL_checkudata(L, -1, myClassName);
	sprintf_s(buf, sizeof(buf), "(%f, %f, %f, %f)", self->x, self->y, self->z, self->w);
	lua_pushstring(L, buf);
	return 1;
}

static int Vec4NewIndex(lua_State *L)
{
	DumpStack();
	Vec4* self = (Vec4*)luaL_checkudata(L, -3, myClassName);
	const char* key = lua_tostring(L, -2);
	Vec4* src = (Vec4*)luaL_checkudata(L, -1, myClassName);
	if (!self || !src || !key) {
		return 0;	// error
	}
	char key4[4] = {'\0', '\0', '\0', '\0'};
	memcpy(key4, key, std::min((size_t)4, strlen(key)));
	vec4IndexByChar(*self, key4[0]) = src->x;
	vec4IndexByChar(*self, key4[1]) = src->y;
	vec4IndexByChar(*self, key4[2]) = src->z;
	vec4IndexByChar(*self, key4[3]) = src->w;
	return 1;
}

static int Vec4Index(lua_State *L)
{
	DumpStack();
	const char* key = lua_tostring(L, -1);
	Vec4* src = (Vec4*)luaL_checkudata(L, -2, myClassName);
	if (!key || !src) {
		return 0;	// error
	}
	int keyLen = strlen(key);

	DumpStack();
	Vec4* ret = (Vec4*)lua_newuserdata(L, sizeof(Vec4));
	luaL_getmetatable(L, myClassName);
	lua_setmetatable(L, -2);
	DumpStack();

	ret->x = keyLen < 1 ? 0 : vec4IndexByChar(*src, key[0]);
	ret->y = keyLen < 2 ? 0 : vec4IndexByChar(*src, key[1]);
	ret->z = keyLen < 3 ? 0 : vec4IndexByChar(*src, key[2]);
	ret->w = keyLen < 4 ? 0 : vec4IndexByChar(*src, key[3]);
	return 1;
}

static int Vec4New(lua_State *L)
{
	int top = lua_gettop(L);
	Vec4 v;
	v.x = top < 4 ? 0 : (float)lua_tonumber(L, -4);
	v.y = top < 3 ? 0 : (float)lua_tonumber(L, -3);
	v.z = top < 2 ? 0 : (float)lua_tonumber(L, -2);
	v.w = top < 1 ? 0 : (float)lua_tonumber(L, -1);
	DumpStack();
	Vec4* p = (Vec4*)lua_newuserdata(L, sizeof(Vec4));
	*p = v;
	DumpStack();
	luaL_getmetatable(L, myClassName);
	DumpStack();
	lua_setmetatable(L, -2);
	DumpStack();
	return 1;
}

void BindVec4()
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
	lua_pushcfunction(L, Vec4Index);
	DumpStack();
	lua_settable(L, -3);
	DumpStack();

	lua_pushstring(L, "__tostring");
	lua_pushcfunction(L, Vec4ToString);
	DumpStack();
	lua_settable(L, -3);
	DumpStack();


//	lua_pushstring(L, "__index");
//	lua_pushcfunction(L, IndexObject);
//	DumpStack();
//	lua_settable(L, -3);
//	DumpStack();

	lua_pushstring(L, "__newindex");
	lua_pushcfunction(L, Vec4NewIndex);
	DumpStack();
	lua_settable(L, -3);
	DumpStack();

	lua_pop(L, 1);
	lua_register(L, "Vec4", Vec4New);
}

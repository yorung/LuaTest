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

static int Vec4GetLength(lua_State *L)
{
	Vec4* self = (Vec4*)luaL_checkudata(L, -1, myClassName);
	float l = length(*self);
	lua_pushnumber(L, l);
	return 1;
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
	aflDumpStack();
	Vec4* self = (Vec4*)luaL_checkudata(L, -3, myClassName);
	const char* key = lua_tostring(L, -2);
	if (!self || !key) {
		return 0;	// error
	}
	int srcType = lua_type(L, -1);
	Vec4 src;
	Vec4* srcPtr;
	switch (srcType) {
	default:
		return 0;	// error
	case LUA_TNUMBER:
		src.x = src.y = src.z = src.w = (float)lua_tonumber(L, -1);
		break;
	case LUA_TUSERDATA:
		if (!(srcPtr = (Vec4*)luaL_checkudata(L, -1, myClassName))) {
			return 0;	// error
		}
		src = *srcPtr;
		break;
	}
	char key4[4] = {'\0', '\0', '\0', '\0'};
	memcpy(key4, key, std::min((size_t)4, strlen(key)));
	vec4IndexByChar(*self, key4[0]) = src.x;
	vec4IndexByChar(*self, key4[1]) = src.y;
	vec4IndexByChar(*self, key4[2]) = src.z;
	vec4IndexByChar(*self, key4[3]) = src.w;
	return 1;
}

static int Vec4Index(lua_State *L)
{
	aflDumpStack();
	const char* key = lua_tostring(L, -1);
	if (!strcmp(key, "GetLength")) {
		lua_pushcfunction(L, Vec4GetLength);
		return 1;
	}
	Vec4* src = (Vec4*)luaL_checkudata(L, -2, myClassName);
	if (!key || !src) {
		return 0;	// error
	}
	int keyLen = strlen(key);

	aflDumpStack();
	Vec4* ret = (Vec4*)lua_newuserdata(L, sizeof(Vec4));
	luaL_getmetatable(L, myClassName);
	lua_setmetatable(L, -2);
	aflDumpStack();

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
	aflDumpStack();
	Vec4* p = (Vec4*)lua_newuserdata(L, sizeof(Vec4));
	*p = v;
	aflDumpStack();
	luaL_getmetatable(L, myClassName);
	aflDumpStack();
	lua_setmetatable(L, -2);
	aflDumpStack();
	return 1;
}

void BindVec4()
{
	aflDumpStack();
	int r = luaL_newmetatable(L, myClassName);
	assert(r);
	aflDumpStack();

	static struct luaL_Reg methods[] =
	{
		{"__tostring", Vec4ToString},
		{"__index", Vec4Index },
		{"__newindex", Vec4NewIndex },
		{nullptr, nullptr},
	};
	luaL_setfuncs(L, methods, 0);
	aflDumpStack();

	lua_pop(L, 1);
	lua_register(L, "Vec4", Vec4New);
}

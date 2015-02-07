print("---------------Vec4 instance creation")
local v = Vec4()

print("---------------v's metatable")
local m = getmetatable(v)
for k,v in pairs(m) do
	print(k, v)
end

print("---------------vector operation")

print("value of v: ", v)

v.xyzw = Vec4(1, 2, 3, 4)
print("value of v: ", v)

v.wzyx = Vec4(1, 2, 3, 4)
print("value of v: ", v)

local vv = v.wzyx
print("value of vv: ", vv)

v.xyzw = Vec4(1.111, 2.2222, 3.333, 4.444).wzyx
print("value of v: ", v)

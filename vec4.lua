print("---------------Vec4 instance creation")
local v = Vec4()

print("---------------v's metatable")
local m = getmetatable(v)
for k,v in pairs(m) do
	print(k, v)
end

print("---------------vector operation")

print("made with default constructor: ", v)
v = Vec4(1, 2, 3, 4)
print("made with parameters: ", v)

v.wzyx = Vec4(1, 2, 3, 4)
print("shader like component set: ", v)

v = Vec4(1.111, 2.2222, 3.333, 4.444).wzyx
print("right value component test", v)

v.w = 0
print("clear w component: ", v)

print("length: ", v:GetLength())


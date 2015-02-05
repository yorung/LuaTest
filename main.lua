print("---------------MyClass instance creation")
local obj = MyClass()

print("---------------printer creation")
local pri = CreatePrinter()
print("---------------printer test")
pri()
pri("message from lua")
pri(1234)

print("---------------obj's metatable")
local m = getmetatable(obj)
for k,v in pairs(m) do
	print(k, v)
end
print("---------------_G")

storedItIntoGlobal = "stored string in global"

local cnt = 0
for k, v in pairs(_G) do
	print(k, v)
	cnt = cnt + 1
end



print("there are "..tostring(cnt).." global variables" )
print("length of _G: "..tostring(#_G))


print("---------------methods")
obj:TestMethod()

--print("value ob abc:", obj.abc)
--obj:SetValue(567)
--print("value ob abc:", obj.abc)

obj.def = "my string"

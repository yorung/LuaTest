print("---------------MyClass instance creation")
local obj = MyClass()

print("---------------obj's metatable")
local m = getmetatable(obj)
for k,v in pairs(m) do
	print(k, v)
end

print("---------------methods")
obj:TestMethod()

--print("value of abc:", obj.abc)
--obj:SetValue(567)
--print("value of abc:", obj.abc)

obj.def = "my string"

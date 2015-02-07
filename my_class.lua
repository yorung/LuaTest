print("---------------MyClass instance creation")
local obj = MyClass()

print("---------------obj's metatable")
local m = getmetatable(obj)
for k,v in pairs(m) do
	print(k, v)
end

print("---------------methods")

obj:SetValue(1234)
print("My value is", obj:GetValue())

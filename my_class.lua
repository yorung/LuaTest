print("---------------MyClass instance creation")
local obj = MyClass()
obj:SetValue(1234)

local function Debug()
	print("---------------obj's metatable")
	local m = getmetatable(obj)
	for k,v in pairs(m) do
		print(k, v)
	end

	print("---------------methods")
	print("My value is", obj:GetValue())
end
--Debug()

return obj, "a hidden message from my_class.lua"

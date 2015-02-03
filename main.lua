local obj = CreateObject(123, "aaa", {12345})
local pri = CreatePrinter()
pri()
pri("message from lua")
pri(1234)

print("value ob abc:", obj.abc)
obj:SetValue(567)
print("value ob abc:", obj.abc)

obj.def = "my string"

local m = getmetatable(obj)
for k,v in pairs(m) do
	print(k, v)
end

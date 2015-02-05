print("---------------Vec4 instance creation")
local v = Vec4()

print("---------------v's metatable")
local m = getmetatable(v)
for k,v in pairs(m) do
	print(k, v)
end

print("---------------methods")
v:SetValue(v)

--print("value ob abc:", v.abc)
--v:SetValue(567)
--print("value ob abc:", v.abc)

v.def = "my string"

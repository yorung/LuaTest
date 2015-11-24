local function DumpTable(tbl)
	storedItIntoGlobal = "stored string in global"

	local cnt = 0
	for k, v in pairs(tbl) do
		print(k, v)
		cnt = cnt + 1
	end

	print("there are "..tostring(cnt).." variables" )
	print("length of table: "..tostring(#tbl))
end

local function DumpGlobal()
	DumpTable(_G)
end

local function DumpLoaded()
	print("--------------------------Dump package.loaded")
	DumpTable(package.loaded)
end

DumpLoaded()
require "bind_win"
--require "mes_box"
require "vec4"
local obj1, msg1 = require("my_class")
obj1:SetValue(5678)
local obj2, msg2 = require("my_class")
local obj3, msg3 = dofile("my_class.lua")
print("value of obj1 from main.lua", obj1:GetValue(), msg1)
print("value of obj2 from main.lua", obj2:GetValue(), msg2)
print("value of obj3 from main.lua", obj3:GetValue(), msg3)
DumpLoaded()

print("--------------------------Dump package.searchers")
DumpTable(package.searchers)
print("---------------_G")
DumpTable(_G)
print("---------------TestNameSpace")
DumpTable(TestNameSpace)
print("---------------End of main.lua")

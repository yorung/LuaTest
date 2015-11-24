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
require "mes_box"
require "vec4"
local obj = dofile("my_class.lua")
print("Get my value from main.lua", obj:GetValue())
DumpLoaded()

print("--------------------------Dump package.searchers")
DumpTable(package.searchers)

print("---------------_G")
DumpTable(_G)
print("---------------TestNameSpace")
DumpTable(TestNameSpace)

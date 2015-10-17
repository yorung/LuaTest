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

print("main.lua executing...")

dofile("bind_win.lua")
dofile("mes_box.lua")
dofile("my_class.lua")
dofile("vec4.lua")

print("---------------_G")
DumpTable(_G)
print("---------------TestNameSpace")
DumpTable(TestNameSpace)

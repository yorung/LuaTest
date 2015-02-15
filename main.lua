local function DumpGlobal()
	print("---------------_G")

	storedItIntoGlobal = "stored string in global"

	local cnt = 0
	for k, v in pairs(_G) do
		print(k, v)
		cnt = cnt + 1
	end

	print("there are "..tostring(cnt).." global variables" )
	print("length of _G: "..tostring(#_G))
end

print("main.lua executing...")

dofile("bind_win.lua")
dofile("mes_box.lua")
dofile("my_class.lua")
dofile("vec4.lua")

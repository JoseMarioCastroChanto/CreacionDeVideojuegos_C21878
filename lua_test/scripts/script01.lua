-- VARIABLES GLOBALES

var_nombre = "Jose Mario Castro"
var_edad = 21

table_config = {
    title = "tarea 01 con LUA",
    fullscreen = true,
    resolution = {
        width = 800,
        height = 600,
    },
}

function factorial(n)
    if n == 1 then
        return 1
    end
    return n * factorial (n-1)
end

print("[LUA] script01.lua")
print("[LUA] var_nombre: "..var_nombre)
print("[LUA] var_edad: "..var_edad)

var_pow = pow(2,4)
print("[LUA] 2^4 = "..var_pow)
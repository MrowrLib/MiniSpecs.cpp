add_rules("mode.debug", "mode.release")

if not is_plat("windows") then
    set_languages("cxx11")
end

includes("*/xmake.lua")

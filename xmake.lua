add_rules("mode.debug", "mode.release")

if not is_plat("windows") then
    set_languages("cxx11")
    add_rules("plugin.compile_commands.autoupdate", { outputdir = "compile_commands" })
end

includes("*/xmake.lua")

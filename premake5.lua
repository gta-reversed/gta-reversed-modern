--[[
    GTA_reversed Build Script
    Use 'premake5 --help' for help
--]]


--[[
    Options and Actions
--]]

newoption {
    trigger     = "outdir",
    value       = "path",
    description = "Output directory for the build files"
}
newoption {
    trigger     = "allow-script-cmd-hooks",
    description = "Whenever script command hooks should be generated (Slows down (full) build by a lot)"
}

if not _OPTIONS["outdir"] then
    _OPTIONS["outdir"] = "build"
end


--[[
    The Solution
--]]

solution "gta_reversed"
    configurations { "Release", "Debug" }

    location(_OPTIONS["outdir"])
    targetprefix "" -- no 'lib' prefix on gcc
	targetdir("bin/" .. "%{cfg.buildcfg}")
    
    filter "configurations:Debug*"
        staticruntime "off"
        symbols "On"
        runtime "Debug"

    filter "configurations:Release*"
        staticruntime "off"
        symbols "On"
        defines { "NDEBUG" }
        runtime "Release"
        optimize "Full"

    configuration "vs*"
        flags { "MultiProcessorCompile" }
        linkoptions   { "/ignore:4099,4251,4275" }
        buildoptions { "/EHsc", "/Zc:preprocessor", "/bigobj" }
        disablewarnings { 26812, 26495, 4099, 4251, 4275 }

    filter "files:libs/**"
        warnings "Off"

    filter {}

    characterset "MBCS"  -- Fix strings
    staticruntime "On" 
    rtti "Off"

    flags {
        "NoImportLib",
        "NoBufferSecurityCheck"
    }

    defines { 
        "_CRT_SECURE_NO_WARNINGS", 
        "_SCL_SECURE_NO_WARNINGS",
        "FatalWarnings"
    }

group "Dependencies"
    defines { "WIN32", "_WINDOWS" }

    project "ogg"
        includedirs { "libs/vorbis/include", "libs/ogg/include", "libs/ogg/include" }
        language "C++"
        kind "StaticLib"
        targetname "ogg"
        warnings "Off"

        vpaths {
            ["Headers/*"] = {"libs/ogg/**.h",},
            ["Sources/*"] = {"libs/ogg/**.c",},
            ["*"] = {"premake5.lua", "CMakeLists.txt"}
        }

        files {
            "libs/ogg/**.h",
            "libs/ogg/**.c"
        }

    project "vorbis"
        includedirs { "libs/vorbis/include", "libs/ogg/include", "%{cfg.targetdir}" }
        language "C++"
        kind "StaticLib"
        targetname "vorbis"

        vpaths {
            ["Headers/*"] = {"libs/vorbis/**.h",},
            ["Sources/*"] = {"libs/vorbis/**.c",},
            ["*"] = {"premake5.lua", "CMakeLists.txt"}
        }

        files { 
            "libs/vorbis/win32/vorbis.def", 
            "libs/vorbis/lib/**.*"
        }
        removefiles {
            "libs/vorbis/lib/psytune.c",
            "libs/vorbis/lib/tone.c",
            "libs/vorbis/lib/misc.c",
            "libs/vorbis/lib/psy.h",
        }

    project "vorbisenc"
        includedirs { "libs/vorbis/include", "libs/ogg/include", "%{cfg.targetdir}" }
        language "C++"
        kind "StaticLib"
        targetname "vorbisenc"
        warnings "Off"
        
        vpaths {
            ["Sources/*"] = {"libs/vorbis/**.c",},
            ["*"] = {"premake5.lua", "CMakeLists.txt"}
        }

        files { 
            "libs/vorbis/lib/vorbisenc.c", 
            "/libs/vorbis/win32/vorbisenc.def" 
        }

    project "vorbisfile"
        includedirs { "libs/vorbis/include", "libs/ogg/include", "%{cfg.targetdir}" }
        language "C++"
        kind "StaticLib"
        targetname "vorbisfile"   
        warnings "Off"

        vpaths {
            ["Sources/*"] = {"libs/vorbis/**.c",},
            ["*"] = {"premake5.lua", "CMakeLists.txt"}
        }

        files { 
            "libs/vorbis/lib/vorbisfile.c", 
            "/libs/vorbis/win32/vorbisfile.def" 
        }

    project "imgui"
        includedirs { "libs/imgui", "libs/imgui/backends", "libs/imgui/misc/cpp" }
        language "C++"
        kind "StaticLib"
        targetname "imgui" 

        vpaths {
            ["Headers/*"] = {"libs/imgui/**.h",},
            ["Sources/*"] = {"libs/imgui/**.c*",},
            ["*"] = {"premake5.lua", "CMakeLists.txt"}
        }

        local filePaths = {
            "imconfig.h", "imgui.h", "imgui_internal.h", "imstb_rectpack.h", "imstb_textedit.h", "imstb_truetype.h", 
            "imgui.cpp", "imgui_draw.cpp", "imgui_widgets.cpp", "imgui_tables.cpp", "imgui_demo.cpp"
        }
        for i, fileName in pairs(filePaths) do 
            filePaths[i] = "libs/imgui/"..fileName
        end
        files {
            "libs/imgui/backends/imgui_impl_win32.h",
            "libs/imgui/backends/imgui_impl_win32.cpp",
            "libs/imgui/backends/imgui_impl_dx9.h",
            "libs/imgui/backends/imgui_impl_dx9.cpp",
            "libs/imgui/misc/cpp/imgui_stdlib.h",
            "libs/imgui/misc/cpp/imgui_stdlib.cpp",
            table.unpack(filePaths),
        }

group ""
    project "gta_reversed"
        cppdialect "C++20"        
        kind "SharedLib"
        targetname "gta_reversed"
        targetextension ".asi"

        pchheader "StdInc.h"
        pchsource "source/StdInc.cpp"

        vpaths {
            ["Headers/*"] = {"source/**.h*",},
            ["Sources/*"] = {"source/**.c*",},
            ["*"] = {"premake5.lua", "CMakeLists.txt"}
        }
     
        files {
            "source/StdInc.h",
            "source/StdInc.cpp",
            "source/**.h*",
            "source/**.c*"
        }

        defines { 
            "NOMINMAX", 
            "USE_GTASA_ALLOCATOR", 
            "EXTRA_DEBUG_FEATURES", 
            "FIX_BUGS" 
        }

        includedirs {
            "source", "source/**",
            "libs/vorbis/include",
            "libs/ogg/include",
            "libs/imgui", "libs/imgui/backends", "libs/imgui/misc/cpp",
            "libs/dxsdk"
        }

        links { 
            "ogg", 
            "vorbis", 
            "vorbisenc", 
            "vorbisfile", 
            "imgui" 
        }

        libdirs { 
            "%{cfg.targetdir}/ogg.lib", 
            "%{cfg.targetdir}/vorbis.lib", 
            "%{cfg.targetdir}/vorbisfile.lib", 
            "%{cfg.targetdir}/vorbisenc.lib",  
            "%{cfg.targetdir}/imgui.lib", 
            "libs/dxsdk/d3d9.lib", 
            "libs/dxsdk/dinput.lib"
        }

        filter {"vs*", "options:allow-script-cmd-hooks"}
            buildoptions { "/bigobj"}

        filter {"options:allow-script-cmd-hooks"}
            defines { "ENABLE_SCRIPT_COMMAND_HOOKS" }   

        filter {} -- Clear filter

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

    filter "action:vs*"
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
            "source", 
            "source/**",
            "libs/vorbis/include",
            "libs/ogg/include",
            "libs/imgui", 
            "libs/imgui/backends", 
            "libs/imgui/misc/cpp",
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

    group "Dependencies"
        defines { "WIN32", "_WINDOWS" }
        include "libs/"

project "gta_reversed"
    cppdialect "C++20"        
    kind "SharedLib"
    targetname "gta_reversed"
    targetextension ".asi"

    pchheader "StdInc.h"
    pchsource "StdInc.cpp"
 
    filter {"options:allow-script-cmd-hooks"}
        defines { "ENABLE_SCRIPT_COMMAND_HOOKS" }

    filter {} -- Clear filter

    vpaths {
        ["Headers/*"] = {"**.h*",},
        ["Sources/*"] = {"**.c*",},
        ["*"] = {"premake5.lua", "CMakeLists.txt"}
    }
    
    files {
        "StdInc.h",
        "StdInc.cpp",
        "**.h*",
        "**.c*"
    }

    includedirs {
        ".",
        "./**",
        "../libs/vorbis/include",
        "../libs/ogg/include",
        "../libs/imgui", 
        "../libs/imgui/backends", 
        "../libs/imgui/misc/cpp",
        "../libs/dxsdk",
        "../libs/tracy/public",
    }
    
    defines { 
        "NOMINMAX", 
        "USE_GTASA_ALLOCATOR", 
        "EXTRA_DEBUG_FEATURES", 
        "FIX_BUGS",

        "TRACY_ENABLE",
        "TRACY_ON_DEMAND",
        "TRACY_CALLSTACK"
    }

    links { 
        "ogg", 
        "vorbis", 
        "vorbisenc", 
        "vorbisfile", 
        "imgui",
        "tracy",
        "ddraw.lib",
        "Winmm.lib",
        "dxguid.lib",
        "strmiids.lib",
        "dsound.lib",
        "d3d9.lib"
    }

    libdirs { 
        "../%{cfg.targetdir}/ogg.lib", 
        "../%{cfg.targetdir}/vorbis.lib", 
        "../%{cfg.targetdir}/vorbisfile.lib", 
        "../%{cfg.targetdir}/vorbisenc.lib",  
        "../%{cfg.targetdir}/imgui.lib", 
        "../libs/dxsdk/d3d9.lib", 
        "../libs/dxsdk/dinput.lib",
    }

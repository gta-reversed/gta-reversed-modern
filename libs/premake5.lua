project "ogg"
    language "C++"
    kind "StaticLib"
    targetname "ogg"
    warnings "Off"
    
    vpaths {
        ["Headers/*"] = {"ogg/**.h",},
        ["Sources/*"] = {"ogg/**.c",},
        ["*"] = {"premake5.lua", "CMakeLists.txt"}
    }

    files {
        "ogg/**.h",
        "ogg/**.c"
    }

    includedirs { 
        "vorbis/include", 
        "ogg/include", 
        "ogg/include" 
    }

project "vorbis"
    language "C++"
    kind "StaticLib"
    targetname "vorbis"
    warnings "Off"

    vpaths {
        ["Headers/*"] = {"vorbis/**.h",},
        ["Sources/*"] = {"vorbis/**.c",},
        ["*"] = {"premake5.lua", "CMakeLists.txt"}
    }

    files { 
        "vorbis/win32/vorbis.def", 
        "vorbis/lib/**.*"
    }

    removefiles {
        "vorbis/lib/psytune.c",
        "vorbis/lib/tone.c",
        "vorbis/lib/misc.c",
        "vorbis/lib/psy.h",
    }

    includedirs { 
        "vorbis/include", 
        "ogg/include", 
        "%{cfg.targetdir}" 
    }

project "vorbisenc"
    language "C++"
    kind "StaticLib"
    targetname "vorbisenc"
    warnings "Off"
    
    vpaths {
        ["Sources/*"] = {"vorbis/**.c",},
        ["*"] = {"premake5.lua", "CMakeLists.txt"}
    }

    files { 
        "vorbis/lib/vorbisenc.c", 
        "/vorbis/win32/vorbisenc.def" 
    }

    includedirs { 
        "vorbis/include", 
        "ogg/include", 
        "%{cfg.targetdir}" 
    }


project "vorbisfile"
    language "C++"
    kind "StaticLib"
    targetname "vorbisfile"   
    warnings "Off"

    vpaths {
        ["Sources/*"] = {"vorbis/**.c",},
        ["*"] = {"premake5.lua", "CMakeLists.txt"}
    }

    files { 
        "vorbis/lib/vorbisfile.c", 
        "/vorbis/win32/vorbisfile.def" 
    }

    includedirs { 
        "vorbis/include", 
        "ogg/include", 
        "%{cfg.targetdir}" 
    }

project "imgui"
    language "C++"
    kind "StaticLib"
    targetname "imgui" 
    warnings "Off"

    vpaths {
        ["Headers/*"] = {"imgui/**.h*",},
        ["Sources/*"] = {"imgui/**.c*",},
        ["*"] = {"premake5.lua", "CMakeLists.txt"}
    }

    files {
        "imgui/backends/imgui_impl_win32.h",
        "imgui/backends/imgui_impl_win32.cpp",
        "imgui/backends/imgui_impl_dx9.h",
        "imgui/backends/imgui_impl_dx9.cpp",
        "imgui/misc/cpp/*.*",
        "imgui/*.*",
    }

    includedirs { 
        "imgui", 
        "imgui/backends", 
        "imgui/misc/cpp" 
    }

project "tracy"
    language "C++"
    kind "StaticLib"
    targetname "tracy"
    warnings "Off"

    vpaths {
        ["Headers/*"] = {"tracy/**.h*",},
        ["Sources/*"] = {"tracy/**.cpp",},
        ["*"] = {"premake5.lua", "CMakeLists.txt"}
    }

    includedirs {
        "tracy/public/"
    }

    files {
        "tracy/public/TracyClient.cpp",
    }

    defines {
        "TRACY_ENABLE" -- Remove this to disable Tracy
    }

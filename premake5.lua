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
if not _OPTIONS["outdir"] then
    _OPTIONS["outdir"] = "Build"
end


--[[
    The Solution
--]]
solution "gta_reversed"

    configurations { "Release", "Debug" }

    location( _OPTIONS["outdir"] )
    targetprefix "" -- no 'lib' prefix on gcc
    targetdir "Bin"
    implibdir "Bin"

    flags {
        characterset ("MBCS"), --fix strings
        staticruntime("On"),
        "NoImportLib",
        rtti ("Off"),
        "NoBufferSecurityCheck"
    }
    vpaths {
        ["Headers/*"] = {"source/**.h*",},
        ["Sources/*"] = {"source/**.c*",},
        ["*"] = {"premake5.lua", "CMakeLists.txt"}
    }
    defines {
            "NOMINMAX" 
    }
    defines {
        "_CRT_SECURE_NO_WARNINGS",
    "_SCL_SECURE_NO_WARNINGS",
    }

    includedirs {
       "source",
       "source/**"
    }
    libdirs {"source"}
    links {"detours"}
    
    configuration "Debug*"
        flags { symbols ("On") }
        
    configuration "Release*"
        defines { "NDEBUG" }
    flags { symbols ("Off") }
        optimize "Full"

    configuration "vs*"
         linkoptions   { "/ignore:4099" }      
         buildoptions {"/EHsc"}
    project "gta_reversed"
        language "C++"
        kind "SharedLib"
        targetname "gta_reversed"
        targetextension ".dll"
        pchheader "StdInc.h"
    pchsource "source/StdInc.cpp"           
        flags { }
       
        files {
        "source/StdInc.h",
        "source/StdInc.cpp",
        "source/**.h*",
        "source/**.c*"
        }
        
        excludes{
        "source/**/errcom.def", --bugfix for premake5
        "source/**/errcore.def"
        }
        


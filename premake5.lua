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
    targetdir("bin/%{cfg.buildcfg}")
    
    filter "configurations:Debug*"
        staticruntime "off"
        symbols "On"
        runtime "Debug"
        vectorextensions "AVX2"
        defines { "NOTSA_DEBUG" }

    filter "configurations:Release*"
        staticruntime "off"
        symbols "On"
        runtime "Release"
        vectorextensions "AVX2"
        defines { "NDEBUG" }
        optimize "Full"
        flags { "LinkTimeOptimization" }

    filter "action:vs*"
        flags { "MultiProcessorCompile" }
        linkoptions   { "/ignore:4099,4251,4275" }
        buildoptions { "/EHsc", "/Zc:preprocessor", "/bigobj", "/utf-8" }
        disablewarnings { 26812, 26495, 4275, 4251, 4200, 4099 }

    filter "files:libs/**"
        warnings "Off"

    filter {}

    characterset "MBCS"  -- Fix strings
    staticruntime "On" 
    rtti "Off"

    flags {
        "NoImportLib",
        --"NoBufferSecurityCheck"
        "FatalWarnings",
    }

    include "source/"

    group "Dependencies"
        defines { "WIN32", "_WINDOWS" }
        include "libs/"

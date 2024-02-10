include "Scripts/Premake/IDE/solution_items.lua"
include "Dependencies.lua"

workspace "VoxForge"
    configurations { "Debug", "Release" }
    targetdir "build"
    startproject "VoxForge-Studio"
    conformancemode "On"

    language "C++"
    cppdialect "C++20"
    staticruntime "Off"

    solution_items { ".editorconfig" }    

    flags { "MultiProcessorCompile" }
    
    defines { "_CRT_SCURE_NO_WARNINGS"}

    filter "action:vs*"
        linkoptions { "/ignore:4099" }
        disablewarnings { "4068" }

    filter "language:C++ or language:C"
        architecture "x86_64"

    filter "configurations:Debug"
        optimize "Off"
        symbols "On"

    filter "configurations:Release"
        optimize "On"
        symbols "Default"

    filter "system:windows"
        buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Forge"
    include "VoxForge"
group ""

group "Studio"
    include "VoxForge-Studio"
group ""

group "Dependencies"
    include "VoxForge/vendor/GLFW"
group ""
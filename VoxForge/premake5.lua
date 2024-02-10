project "VoxForge"
    kind "StaticLib"

    targetdir ("%{wks.location}/build/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/build/bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "vfpch.hpp"
    pchsource "src/vfpch.cpp"

    files {
        "src/**.hpp",
        "src/**.cpp",
    }

    includedirs { "src/", "vendor/", }

    IncludeDependencies()

    filter "configurations:Debug"
        symbols "On"
        defines { "VF_DEBUG", "_DEBUG", } 

    filter "configurations:Release"
        optimize "On"
        defines { "VF_RELEASE", "NDEBUG", }
project "VoxStudio"
    kind "ConsoleApp"

    targetdir ("%{wks.location}/build/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/build/bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "src/**.hpp",
        "src/**.cpp",
    }

    includedirs {
        "src/",

        "%{wks.location}/VoxForge/src/",
        "%{wks.location}/VoxForge/vendor/",
    }

    links {
        "VoxForge"
    }

    warnings "Extra"

    filter "configurations:Debug"
        symbols "On"
        defines { "VF_DEBUG" }
        ProcessDependencies("Debug")

    filter "configurations:Release"
        optimize "On"
        defines { "VF_RELEASE" }
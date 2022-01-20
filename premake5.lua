workspace "SnakeGame"
    architecture "x64"
    configurations
    {
        "Debug",
        "Release"
    }
    startproject "snakeGame"
    outputdir = "%{cfg.buildcfg}"
    SFML_VERSION = "SFML-2.5.1"

project "snakeGame"
    location "snakeGame"
    kind "ConsoleApp"
    language "C++"
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
    pchheader "sgpch.h"
    pchsource "snakeGame/sgpch.cpp"
    files
    {
        "%{prj.name}/**.h",
        "%{prj.name}/**.cpp",
    }
    includedirs
    {
        "SFML-2.5.1/include",
        "snakeGame/"
    }
    libdirs
    {
        "SFML-2.5.1/lib",
    }
filter "system:windows"
    system "windows"
    cppdialect "C++17"
    systemversion "latest"
filter { "system:windows", "kind:WindowedApp or ConsoleApp" }
    entrypoint "mainCRTStartup"
filter "configurations:Debug"
        defines "DEBUG"
        symbols "on"
        links
        {
            "sfml-audio-d.lib",
            "sfml-window-d.lib",
            "sfml-graphics-d.lib",
            "sfml-system-d.lib"
        }
        postbuildcommands {
            ("{COPY} ../"..SFML_VERSION.."/bin/**-d-2.dll %{cfg.targetdir}"),
        }


filter "configurations:Release"
        runtime "Release"
        defines "RELEASE"
        optimize "on"
        links
        {
            "sfml-audio.lib",
            "sfml-window.lib",
            "sfml-graphics.lib",
            "sfml-system.lib"
        }
        postbuildcommands {
            ("{COPY} ../"..SFML_VERSION.."/bin/sfml-audio-2.dll %{cfg.targetdir}"),
            ("{COPY} ../"..SFML_VERSION.."/bin/sfml-window-2.dll %{cfg.targetdir}"),
            ("{COPY} ../"..SFML_VERSION.."/bin/sfml-graphics-2.dll %{cfg.targetdir}"),
            ("{COPY} ../"..SFML_VERSION.."/bin/sfml-system-2.dll %{cfg.targetdir}"),
        }


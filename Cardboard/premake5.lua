project "Cardboard"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    staticruntime "off"

    targetdir ("%{wks.location}/bin/" .. OUTPUT_DIR .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. OUTPUT_DIR .. "/%{prj.name}")

    files
    {
        "Source/**.hpp",
        "Source/**.cpp"
    }

    includedirs
    {
        "Source",
        "Vendor/glfw/include"
    }

    links
    {
        "GLFW",
        "opengl32.lib"
    }

    filter "configurations:Debug"
		defines "CB_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "CB_RELEASE"
		runtime "Release"
		optimize "on"
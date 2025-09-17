project "Game"
	kind "ConsoleApp"
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
		"%{wks.location}/Cardboard/Source",
		"%{wks.location}/Cardboard/Vendor/glfw/include",
	}

	links
	{
		"Cardboard"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "CB_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:"
		defines "CB_RELEASE"
		runtime "Release"
		optimize "on"
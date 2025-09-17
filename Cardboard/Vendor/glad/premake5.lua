project "glad"
	kind "StaticLib"
	language "C"
	staticruntime "off"
	warnings "off"

    targetdir ("%{wks.location}/bin/" .. OUTPUT_DIR .. "/%{prj.name}")
    objdir ("%{wks.location}/bin-int/" .. OUTPUT_DIR .. "/%{prj.name}")
    
    files
    {
        "include/glad/gl.h",
        "include/KHR/khrplatform.h",
        "src/gl.c"
    }

    includedirs
    {
        "src",
        "include"
    }
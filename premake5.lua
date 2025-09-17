workspace "Cardboard"
    architecture "x64"
    startproject "Game"

    configurations
    {
        "Debug",
        "Release"
    }

OUTPUT_DIR = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
outputdir = OUTPUT_DIR -- Support for TheCherno's premake files

group "Engine/Deps"

include "Cardboard/Vendor/glfw"

group ""

group "Engine"

    include "Cardboard"

group ""

include "Game"
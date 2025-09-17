workspace "Cardboard"
    architecture "x64"
    startproject "Game"

    configurations
    {
        "Debug",
        "Release"
    }

OUTPUT_DIR = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Engine"

    include "Cardboard"

group ""

include "Game"
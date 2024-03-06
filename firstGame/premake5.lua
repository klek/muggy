-- Creating workspace
-- TODO(klek): Change FirstGame to a stringvalue depending 
-- on the creation of the game
workspace "firstGame"
    configurations 
    { 
        "Debug", 
        "Release" 
    }
    -- NOTE(klek): Architecture cannot be in a table!
    architecture "x64"
    flags 
    { 
        "MultiProcessorCompile" 
    }

    if _TARGET_OS == "windows" then
        startproject "firstGame"
    else
        startproject "firstGame"
    end

    filter "configurations:Debug"
        symbols "on"

    filter "configurations:Release"
        symbols "on"
        --omitframepointer "On"
        flags 
        { 
            "LinkTimeOptimization", 
            "NoBufferSecurityCheck", 
            "NoRuntimeChecks" 
        }
    filter {}
        
    -- Set toolset to GCC on linux
    if _TARGET_OS == "linux" then
--        toolset "gcc"
    end
        
    -- Setup output directories -> Generate a bin folder in the root directory
    outputDir = "%{wks.location}/bin/%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"
    intermediateDir = "%{wks.location}/build/%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"
    -- This is the 
    libDir = "%{wks.location}/../bin/%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"
    muggyIncDir = "%{wks.location}/../muggy"
    glfwIncDir = "%{wks.location}/../muggy/thirdparty/glfw"

project "firstGame"
    location "firstGame"
    kind "ConsoleApp"
    staticruntime "off"
    language "C++"
    cppdialect "C++17"
    targetname "%{prj.name}"
    -- NOTE(klek): Consider to explicitly state which files should be
    --             included
    files 
    { 
        "**.h", 
        "**.cpp" 
    }
    includedirs 
    {
        "%{prj.location}/src",
        (muggyIncDir), 
        (muggyIncDir .. "/engineAPI"), 
        (muggyIncDir .. "/code/core"), 
        (glfwIncDir .. "/include") 
    }
    libdirs
    {
        -- This is relative to the install-dir of the muggy
        -- and glfw lib
        (libDir)
    }
    if _TARGET_OS == "windows" then 
        links 
        {
            "muggy",
            "glfw3"
        }
    else
--        buildoptions 
--        { 
--            "-Wno-switch",
--            "-Wno-missing-field-initializers",
--            "-Wno-unused-parameter", 
--            "-Wno-ignored-qualifiers", 
--            "-Wno-unknown-pragmas", 
--            "-Wno-class-memaccess", 
--            "-Wno-reorder" 
--        }
        links
        {
            "muggy",
            "glfw3",
            "X11"
        }
    end
    targetdir (outputDir)
    objdir ( "!" .. intermediateDir .. "/%{prj.name}" )



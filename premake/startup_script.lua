-- Update submodules
-- os.execute runs from _this_ files location, so we go up one step to
-- get to the root-folder and execute git
-- NOTE(klek): If you have gotten this far, we assume you have git
--             installed
os.execute( "echo [INFO]: Updating git submodules..." )
os.execute( "cd .. && git submodule update --init --recursive" )

-- Build glfw with cmake
if _TARGET_OS == "windows" then
    os.execute( "echo [DEBUG]: This is Windows" )
    -- Copy bat-script for building the cmake environment for
    -- glfw. This bat-script is then called by prebuildcommands
--    os.execute( "copy cmake_glfw_on_windows.bat ../muggy/cmake_glfw_on_windows.bat" )
    os.copyfile( "cmake_glfw_on_windows.bat", "../muggy/cmake_glfw_on_windows.bat" )
    os.copyfile( "cmake_vulkan_build_on_windows.bat", "../muggy/cmake_vulkan_build_on_windows.bat" )
else
    os.execute( "echo [DEBUG]: This is Linux" )
    -- Copy bash-script for building the cmake environment for
    -- glfw. This bash-script is then called by prebuildcommands
    os.copyfile( "cmake_glfw_on_linux.sh" , "../muggy/cmake_glfw_on_linux.sh" )
    os.copyfile( "cmake_vulkan_build_on_linux.sh" , "../muggy/cmake_vulkan_build_on_linux.sh" )
end

-- cmake -S muggy/thirdparty/glfw -B build/linux-x86_64/Debug/Debug/glfw/ -D BUILD_SHARED_LIBS=OFF -D GLFW_BUILD_EXAMPLES=OFF -D GLFW_BUILD_TESTS=OFF -D GLFW_BUILD_DOCS=OFF
-- cmake --build build/linux-x86_64/Debug/Debug/glfw/
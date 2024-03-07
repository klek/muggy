@echo off

set SRC_PATH=%1
set BUILD_PATH=%2
::set LIB_PATH=%BUILD_PATH%\src\Debug\glfw3.lib
set BIN_PATH=%3

set cmake="e:\microsoft\visualstudio\2022\community\common7\ide\commonextensions\microsoft\cmake\CMake\bin\cmake.exe"

:: Building vulkan-loader
%cmake% -S "%SRC_PATH%\vulkan-loader" \
        -B "%BUILD_PATH%\vulkan-loader" \
        -G "Visual Studio 17 2022" \
        -D UPDATE_DEPS=ON
%cmake% --build "%BUILD_PATH%\vulkan-loader"
%cmake% --install "%BUILD_PATH%\vulkan-loader" --prefix "%BIN_PATH%\vulkan-loader"

:: Building vulkan-tools

:: Building vulkan-validationLayers
%cmake% -S "%SRC_PATH%\vulkan-validationLayers" \
        -B "%BUILD_PATH%\vulkan-validationLayers" \
        -G "Visual Studio 17 2022" \
        -D UPDATE_DEPS=ON \
        -D BUILD_WERROR=OFF \
        -D BUILD_TESTS=OFF \
        -D CMAKE_BUILD_TYPE=Debug
%cmake% --build "%BUILD_PATH%\vulkan-validationLayers"
%cmake% --install "%BUILD_PATH%\vulkan-validationLayers" --prefix "%BIN_PATH%\vulkan-validationLayers"

:: Building SPIRV-tools
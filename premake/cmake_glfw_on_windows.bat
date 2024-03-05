@echo off

set SRC_PATH=%1
set BUILD_PATH=%2
set LIB_PATH=%BUILD_PATH%\src\Debug\glfw3.lib
set BIN_PATH=%3

set cmake="e:\microsoft\visualstudio\2022\community\common7\ide\commonextensions\microsoft\cmake\CMake\bin\cmake.exe"

%cmake% -S %SRC_PATH% -B %BUILD_PATH% -G "Visual Studio 17 2022" -D BUILD_SHARED_LIBS=OFF -D GLFW_BUILD_EXAMPLES=OFF -D GLFW_BUILD_TESTS=OFF -D GLFW_BUILD_DOCS=OFF
%cmake% --build %BUILD_PATH%
if not exist %BIN_PATH% mkdir %BIN_PATH%
xcopy /Y "%LIB_PATH%" "%BIN_PATH%"
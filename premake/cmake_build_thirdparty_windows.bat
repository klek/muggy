@echo off

set SRC_PATH=%1
set BUILD_PATH=%2
set BIN_PATH=%3

:: Call glfw cmake script
call cmake_glfw_on_windows.bat %SRC_PATH% %BUILD_PATH% %BIN_PATH%
call cmake_vulkan_build_on_windows.bat %SRC_PATH% %BUILD_PATH% %BIN_PATH%
@echo off

pushd ..
"premake/premake5.exe" --systemscript=premake/startup_script.lua --file=premake5.lua vs2022
popd
pause

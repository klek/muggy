#!/bin/bash

pushd ..
./premake/premake5 --systemscript=premake/startup_script.lua --file=premake5.lua gmake2
popd
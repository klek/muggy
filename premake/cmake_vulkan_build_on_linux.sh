#!/bin/bash

# Internal variables
SRC_PATH="$1"
BUILD_PATH="$2"
#LIB_PATH="$BUILD_PATH/src/libglfw3.a"
BIN_PATH="$3"

# Building vulkan-loader
echo "----"
echo "Generating vulkan-loader project from $SRC_PATH/vulkan-loader to $BUILD_PATH/vulkan-loader ..."
cmake -S "$SRC_PATH/vulkan-loader" \
      -B "$BUILD_PATH/vulkan-loader" \
      -D CMAKE_BUILD_TYPE=Debug \
      -D UPDATE_DEPS=ON 
echo "Building vulkan-loader ..."
cmake --build "$BUILD_PATH/vulkan-loader"
echo "Installing vulkan-loader to: $BIN_PATH/vulkan-loader"
cmake --install "$BUILD_PATH/vulkan-loader" --config Debug --prefix "$BIN_PATH/vulkan-loader"

# Building vulkan-tools
#echo "----"
#echo "Generating vulkan-tools project from $SRC_PATH/vulkan-tools to $BUILD_PATH/vulkan-tools..."
#cmake -S "$SRC_PATH/vulkan-tools" \
#      -B "$BUILD_PATH/vulkan-tools" \
#      -D UPDATE_DEPS=ON \
#      -D BUILD_WERROR=OFF \
#      -D BUILD_TESTS=OFF \
#      -D CMAKE_BUILD_TYPE=Debug
#echo "Building vulkan-tools..."
#cmake --build "$BUILD_PATH/vulkan-tools"
#echo "Installing vulkan-tools to: $BIN_PATH/vulkan-tools"
#cmake --install "$BUILD_PATH/vulkan-tools" --config Debug --prefix "$BIN_PATH/vulkan-tools"

# Building vulkan-validationLayers
echo "----"
echo "Generating vulkan-validationLayers project from $SRC_PATH/vulkan-validationLayers to $BUILD_PATH/vulkan-validationLayers ..."
cmake -S "$SRC_PATH/vulkan-validationLayers" \
      -B "$BUILD_PATH/vulkan-validationLayers" \
      -D UPDATE_DEPS=ON \
      -D BUILD_WERROR=OFF \
      -D BUILD_TESTS=OFF \
      -D CMAKE_BUILD_TYPE=Debug
echo "Building vulkan-validationLayers ..."
cmake --build "$BUILD_PATH/vulkan-validationLayers"
echo "Installing vulkan-validationLayers: $BIN_PATH/vulkan-validationLayers"
cmake --install "$BUILD_PATH/vulkan-validationLayers" --config Debug --prefix "$BIN_PATH/vulkan-validationLayers"

# Building SPIRV-tools
#echo "----"
#echo "Generating spirv-tools project from $SRC_PATH/spirv-tools to $BUILD_PATH/spirv-tools ..."
#cmake -S "$SRC_PATH/spirv-tools" \
#      -B "$BUILD_PATH/spirv-tools" 
#echo "Building spirv-tools..."
#cmake --build "$BUILD_PATH/spirv-tools"
#echo "Installing spirv-tools: $BIN_PATH/spirv-tools"
#cmake --install "$BUILD_PATH/spirv-tools" --config Debug --prefix "$BIN_PATH/spirv-tools"



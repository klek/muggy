#!/bin/bash

SRC_PATH="$1"
BUILD_PATH="$2"
#LIB_PATH="$BUILD_PATH/src/libglfw3.a"
BIN_PATH="$3"

echo "----"
#echo "Using src-path: $SRC_PATH/glfw"
#echo "Using build-path: $BUILD_PATH/glfw"
echo "Generating glfw project.."
cmake -S "$SRC_PATH/glfw" \
      -B "$BUILD_PATH/glfw" \
      -D BUILD_SHARED_LIBS=OFF \
      -D GLFW_BUILD_EXAMPLES=OFF \
      -D GLFW_BUILD_TESTS=OFF \
      -D GLFW_BUILD_DOCS=OFF
echo "Building glfw project..."
cmake --build "$BUILD_PATH/glfw"
echo "Installing glfw to: $BIN_PATH/glfw"
cmake --install "$BUILD_PATH/glfw" --config Debug --prefix "$BIN_PATH/glfw"
#echo Copying library: $LIB_PATH to binary path: $BIN_PATH
#echo Creating symlink: $BIN_PATH to binary: $LIB_PATH
#mkdir -p $BIN_PATH
#cp $LIB_PATH $BIN_PATH
#ln -sf $LIB_PATH $BIN_PATH
echo "GLFW-script completed!"
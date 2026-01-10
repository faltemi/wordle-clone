#!/bin/bash

set -e

BUILD_DIR="build"
EXECUTABLE="./build/wordle"

usage() {
    echo "Usage: $0 [clean|run|rebuild]"
    echo "  (no args) : Configure and Build"
    echo "  clean     : Remove build directory"
    echo "  run       : Build and then run the game"
    echo "  rebuild   : Clean, then build, then run"
    exit 1
}

if [ "$#" -ge 2 ]; then
    echo "Invalid number of arguments"
    usage
    exit 1
fi

if [ "$#" -eq 1 ] && [[ "$1" != "clean" && "$1" != "run" && "$1" != "rebuild" ]]; then
    usage
    exit 1
fi

if [ "$1" == "clean" ] || [ "$1" == "rebuild" ]; then
    echo "Cleaning build directory..."
    rm -rf $BUILD_DIR
    if [ "$1" == "clean" ]; then
        exit 0
    fi
fi

if [ ! -d "$BUILD_DIR" ]; then
    echo "Creating build directory..."
    mkdir $BUILD_DIR
fi

echo "Configuring..."
cd $BUILD_DIR
cmake ..

echo "Building..."
cmake --build .

if [ "$1" == "run" ] || [ "$1" == "rebuild" ]; then
    echo "Running game..."
    cd ..
    if [ -f "$EXECUTABLE" ]; then
        $EXECUTABLE
    else
        echo "Error: Executable not found at $EXECUTABLE"
    fi
fi

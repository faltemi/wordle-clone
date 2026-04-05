This is my attempt at a Wordle clone written in C with raylib.

## Linux Build

```bash
# 1) Install a compiler + cmake
sudo apt update
sudo apt install build-essential cmake

# 2) Install libraries that Raylib needs
sudo apt install git libasound2-dev libx11-dev libxrandr-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev libxinerama-dev

# 3) Configure & build
mkdir build && cd build
cmake ..
cmake --build .

# 4) Run
./wordle
```

## Windows Build

```powershell
# 1) Install prerequisites
#    - Visual Studio 2019+ with "Desktop development with C++" workload
#      (includes MSVC compiler and CMake)
#    OR
#    - Install CMake (https://cmake.org/download/) and MinGW-w64

# 2) Configure & build
mkdir build
cd build
cmake ..
cmake --build . --config Release

# 3) Run
.\Release\wordle.exe
```

**Third Party Assets**

The word list used in this project is sourced from [wordle-list](https://github.com/tabatkins/wordle-list) by [tabatkins](https://github.com/tabatkins), used under the MIT License.
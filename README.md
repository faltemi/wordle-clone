This is my attempt at a Wordle clone written in C with raylib.

**Dependencies**
GCC
Raylib
X11 & audio/OpenGL (for raylib)
Ninja
CMake
MSYS2 (if Windows)

**Linux Build**
# 1) Install a compiler + cmake + ninja
sudo apt update
sudo apt install -y build-essential cmake ninja-build pkg-config

# 2) Install X11
sudo apt install -y libx11-dev libxi-dev libxrandr-dev libxinerama-dev \
  libxcursor-dev libgl1-mesa-dev libasound2-dev libpulse-dev


# 2) Configure & build
cmake -S . -B build -G Ninja
cmake --build build

**Windows Build**
# 1) Install MSYS2

# 2) Install toolchain + raylib
# UCRT64 environment (recommended)
pacman -S --needed --noconfirm \
  mingw-w64-ucrt-x86_64-gcc \
  mingw-w64-ucrt-x86_64-cmake \
  mingw-w64-ucrt-x86_64-ninja \
  mingw-w64-ucrt-x86_64-pkg-config \
  mingw-w64-ucrt-x86_64-raylib

# 3) Configure & build (from same MSYS2 shell)
cd /path/to/your/clone
cmake -S . -B build -G Ninja
cmake --build build

# 4) Run "wordle"
The produced .exe will be in build/. Run it from the same MSYS2 shell to ensure DLLs are on PATH, or copy the needed mingw.../ucrt... DLLs next to your .exe.

**Third Party Assets**

The word list used in this project is sourced from [wordle-list](https://github.com/tabatkins/wordle-list) by [tabatkins](https://github.com/tabatkins), used under the MIT License.
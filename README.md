This is my attempt at a Wordle clone written in C with raylib.

**Linux Build**
# 1) Install a compiler + cmake + ninja
sudo apt update
sudo apt install build-essential

# 2) Install libraries for opening windows/playing audio that Raylib needs
sudo apt install git libasound2-dev libx11-dev libxrandr-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev libxinerama-dev


# 3) Configure & build
mkdir build
cd build
cmake ..
cmake --build .

# 4) Run wordle
Run the binary generated in your build directory.
./wordle

**Windows Build**
ToDo.

**Third Party Assets**

The word list used in this project is sourced from [wordle-list](https://github.com/tabatkins/wordle-list) by [tabatkins](https://github.com/tabatkins), used under the MIT License.
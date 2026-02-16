cmake_minimum_required(VERSION 3.20)

project(WordleClone C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG        5.0
)

# Disable Raylib extras
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(raylib)

set(SOURCES
    src/draw.c
    src/guessing.c
    src/icon.c
    src/inputProcessing.c
    src/main.c
    src/theme.c
    src/wordList.c
    components/src/gameGrid.c
    components/src/keyboard.c
    components/src/notificationManager.c
    components/src/settingsPanel.c
    icons/src/closePanelIcon.c
    icons/src/letterIcon.c
    icons/src/settingsIcon.c
    icons/src/themeIcon.c
    state/src/gameState.c
)

add_executable(wordle ${SOURCES})

# Tells CMake to look in 'include/' for your headers
target_include_directories(wordle PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/components/include
    ${CMAKE_CURRENT_SOURCE_DIR}/icons/include
    ${CMAKE_CURRENT_SOURCE_DIR}/state/include
)

# Raylib handles the platform specifics (gdi32, winmm, pthread, etc.)
# automatically via its own interface usage requirements.
target_link_libraries(wordle PRIVATE raylib)

# Compiler Warnings
if(MSVC)
    target_compile_options(wordle PRIVATE /W4)
else()
    target_compile_options(wordle PRIVATE -Wall -Wextra)
endif()

# Asset Management
add_custom_command(TARGET wordle POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/data
    $<TARGET_FILE_DIR:wordle>/data
)
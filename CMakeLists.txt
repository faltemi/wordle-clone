cmake_minimum_required(VERSION 3.20)
project(WordleClone C)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Options for smaller static builds
option(BUILD_SHARED_LIBS "Build shared libs" OFF)
option(USE_MSVC_RUNTIME_LIBRARY_DLL "Use MSVC DLL runtime" ON)

# Fetch raylib from GitHub at a known-good tag
include(FetchContent)
set(RAYLIB_VERSION 5.0)
FetchContent_Declare(raylib
  GIT_REPOSITORY https://github.com/raysan5/raylib.git
  GIT_TAG ${RAYLIB_VERSION}
)
# Build raylib without its examples/tools to keep it fast
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES OFF CACHE BOOL "" FORCE)
set(BUILD_TESTING OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(raylib)

# Your executable
file(GLOB SRC_FILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")
add_executable(wordle ${SRC_FILES})

# If you keep headers in include/, uncomment:
target_include_directories(wordle PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Link raylib
target_link_libraries(wordle PRIVATE raylib)

# Windows-specific system libs (raylib needs these when using MinGW)
if (WIN32)
  target_compile_definitions(wordle PRIVATE PLATFORM_DESKTOP)
  # MSVC: set runtime (multi-threaded DLL by default)
  if (MSVC AND NOT USE_MSVC_RUNTIME_LIBRARY_DLL)
    foreach(flag_var
      CMAKE_C_FLAGS_DEBUG CMAKE_C_FLAGS_RELEASE
      CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE)
      if(${flag_var} MATCHES "/MD")
        string(REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
      endif()
    endforeach()
  endif()
  if (MINGW)
    target_link_libraries(wordle PRIVATE winmm gdi32)
  endif()
endif()

# Copy assets to build dir for easy F5-run in VS Code
add_custom_command(TARGET wordle POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
          ${CMAKE_SOURCE_DIR}/data
          $<TARGET_FILE_DIR:wordle>/data
)

# Install target (useful for GitHub Releases artifacts)
install(TARGETS wordle RUNTIME DESTINATION .)
install(DIRECTORY data/ DESTINATION data)

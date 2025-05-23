cmake_minimum_required(VERSION 4.0)

project(ChatWindow C)

option(USE_WAYLAND "Use Wayland display server" OFF)

if(USE_WAYLAND)
    set(GLFW_BUILD_WAYLAND ON CACHE BOOL "Use Wayland for window creation" FORCE)
    set(GLFW_BUILD_X11 OFF CACHE BOOL "Use X11 for window creation" FORCE)
endif()

add_subdirectory(
    vendor/raylib
)

file(GLOB_RECURSE SOURCE_FILES 
    src/*.c
    src/components/*.c
)

add_executable(window ${SOURCE_FILES})

target_link_libraries(window PRIVATE raylib)

target_include_directories(window PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/vendor/clay")
target_include_directories(window PRIVATE "include")

target_compile_options(window PRIVATE -Wall -Wextra -Wpedantic)

if(USE_WAYLAND)
    target_compile_definitions(window PRIVATE USE_WAYLAND)
endif()

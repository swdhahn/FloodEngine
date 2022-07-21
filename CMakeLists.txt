cmake_minimum_required(VERSION 3.20)
project(FloodEngine)

SET(x86 FALSE CACHE BOOL "Whether the program is built for x86 or x64 - Default:False")
set(FirstBuild FALSE CACHE BOOL "Builds the entire project if this is the first build - Default:False")

set(UNICODE)

message("Using compiler ${CMAKE_C_COMPILER}")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")

message(CMAKE_BUILD_TYPE)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-D_DEBUG)
    message("Debug mode enabled")
else()
    message("Release mode enabled")
endif()

if(x86)
    message("Building for x86")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m32")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32")
else()
    message("Building for x64")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m64")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64")
endif()

find_package(OpenGL REQUIRED)
#find_package(Vulkan REQUIRED)

file(GLOB_RECURSE lib_program_sources CONFIGURE_DEPENDS "src/*.h" "src/*.cpp")
file(GLOB_RECURSE program_sources CONFIGURE_DEPENDS "test/*.cpp" "test/*.h")

add_library(FloodEngineLIB STATIC ${lib_program_sources})

add_executable(${PROJECT_NAME} ${program_sources})

#include_directories(P:\\sdks\\VulkanSDK\\1.2.162.0\\Include)
include_directories(libs/glew-2.1.0/include)
include_directories(libs/glfw-3.3.4/include)
include_directories(libs/assimp-5.1.4/include)
include_directories(libs/include)

target_include_directories(${PROJECT_NAME} PUBLIC src)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(libs/glfw-3.3.4)
add_subdirectory(libs/glew-2.1.0)

#add_library(assimp INTERFACE)
find_library(assimp NAMES assimpd assimp PATHS ${CMAKE_BINARY_DIR}/libs/assimp-5.1.4/lib REQUIRED)

if(NOT assimp_FOUND)
    add_subdirectory(libs/assimp-5.1.4)
#else()
    #target_link_libraries(${PROJECT_NAME} -lassimp)
endif()

add_definitions(
        -DTW_STATIC
        -DTW_NO_LIB_PRAGMA
        -DTW_NO_DIRECT3D
        -DGLEW_STATIC
        -D_CRT_SECURE_NO_WARNINGS
)

target_link_libraries(${PROJECT_NAME} FloodEngineLIB ${OPENGL_LIBRARY} glfw ${GLFW_LIBRARIES} glew_s ${GLEW_LIBRARIES} assimp)# Vulkan::Vulkan)

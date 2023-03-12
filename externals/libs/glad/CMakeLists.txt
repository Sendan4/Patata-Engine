# LIB_SHARED ON or OFF in Main CMakeLists
message("  - Glad -")
cmake_minimum_required(VERSION 3.24.2)
project(glad)

message(STATUS "Configurando glad - CMakeList Personalizado")

message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")

if (SHARED_BUILD)
    message(STATUS "Shared Build")
    add_library(${PROJECT_NAME} SHARED "src/glad.c")
else()
    message(STATUS "Static Build")
    add_library(${PROJECT_NAME} STATIC "src/glad.c")
endif()

target_include_directories(${PROJECT_NAME} PUBLIC include/)

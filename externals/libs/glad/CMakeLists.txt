# LIB_SHARED ON or OFF in Main CMakeLists

cmake_minimum_required(VERSION 3.24.2)
project(glad)

message(STATUS "Configurando glad - CMakeList Personalizado")

if (SHARED_BUILD)
    add_library(${PROJECT_NAME} SHARED "src/glad.c")
else()
    add_library(${PROJECT_NAME} STATIC "src/glad.c")
endif()

target_include_directories(${PROJECT_NAME} PUBLIC include/)

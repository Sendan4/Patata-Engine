# LIB_SHARED ON or OFF in Main CMakeLists

cmake_minimum_required(VERSION 3.24.2)
project(glad2)

message(STATUS "Configurando Glad 2 - CMakeList Personalizado")

if (BUILD_TYPE)
    add_library(${PROJECT_NAME} SHARED "src/gl.c")
	message(STATUS "Glad 2 - Shared Build")
else()
    add_library(${PROJECT_NAME} STATIC "src/gl.c")
	message(STATUS "Glad 2 - Static Build")
endif()

target_include_directories(${PROJECT_NAME} PUBLIC include/)

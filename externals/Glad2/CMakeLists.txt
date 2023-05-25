# LIB_SHARED ON or OFF in Main CMakeLists

cmake_minimum_required(VERSION 3.24.2)
project(glad2 VERSION 2)

message(STATUS "Configurando Glad 2 - CMakeList Personalizado")

include_directories("include/")

if (SHARED_BUILD)
    if (MSVC)
        set(CMAKE_MSVC_RUNTIME_LIBRARY MultiThreadedDLL)
        add_library(${PROJECT_NAME} "src/gl.c")
    else ()
        add_library(${PROJECT_NAME} SHARED "src/gl.c")
        message(STATUS "Glad 2 - Shared Build")
	endif()
else()
    set(CMAKE_MSVC_RUNTIME_LIBRARY MultiThreaded)
    add_library(${PROJECT_NAME} STATIC "src/gl.c")
	message(STATUS "Glad 2 - Static Build")
endif()

target_include_directories(${PROJECT_NAME} PRIVATE include/)

if (MSVC)
    target_compile_definitions(${PROJECT_NAME} PRIVATE WINDOWS_EXPORT_ALL_SYMBOLS)
endif()
cmake_minimum_required(VERSION 3.18)

message("")
message ("  - Glad2 -")

project(Glad2 LANGUAGES C VERSION 2.0.4)

set(Glad2_VERSION "2.0.4" CACHE INTERNAL "Glad Version")

include(CheckIncludeFile)

CHECK_INCLUDE_FILE("stdint.h" HAVE_STDINT_H)
CHECK_INCLUDE_FILE("inttypes.h" HAVE_INTTYPES_H)

if (LIBS_SHARED_BUILD AND NOT MSVC)
	message(STATUS "Shared Build")
	add_library(${PROJECT_NAME} SHARED include/glad/gl.h include/KHR/khrplatform.h src/gl.c)
else()
	message(STATUS "Static Build")
	add_library(${PROJECT_NAME} STATIC include/glad/gl.h include/KHR/khrplatform.h src/gl.c)

    if (SHARED_BUILD AND CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
		target_compile_options(${PROJECT_NAME} PRIVATE "-fPIC")
		message(STATUS "Build With Position Independent Code")
	endif()
endif()

if (NOT MSVC OR MSYS AND CMAKE_SYSTEM_NAME STREQUAL "Windows")
	enable_language(RC)
	target_sources(${PROJECT_NAME} PRIVATE "src/glad.rc")
endif()

target_include_directories(${PROJECT_NAME} PUBLIC include/)
set_target_properties(${PROJECT_NAME}
	PROPERTIES
	VERSION "${Glad2_VERSION}")

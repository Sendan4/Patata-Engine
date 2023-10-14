cmake_minimum_required(VERSION 3.18)

message("")
message ("  - Glad2 -")

project(Glad2)

include(CheckIncludeFile)

CHECK_INCLUDE_FILE("stdint.h" HAVE_STDINT_H)
CHECK_INCLUDE_FILE("inttypes.h" HAVE_INTTYPES_H)

find_file(HAVE_GL_H "glad/gl.h" PATHS "${CMAKE_CURRENT_SOURCE_DIR}/include/")
find_file(HAVE_KHRPLATFORM_H "KHR/khrplatform.h" PATHS "${CMAKE_CURRENT_SOURCE_DIR}/include/")

if (NOT HAVE_STDINT_H OR NOT HAVE_INTTYPES_H OR NOT HAVE_GL_H)
	message(FATAL_ERROR "include files missing")
else()
	if (HAVE_GL_H)
			message(STATUS "Looking for glad/gl.h - found")
	endif()

	if (HAVE_KHRPLATFORM_H)
			message(STATUS "Looking for KHR/khrplatform.h - found")
	endif()
endif()

if (SHARED_BUILD AND NOT MSVC)
	message(STATUS "Shared Build")
	add_library(${PROJECT_NAME} SHARED include/glad/gl.h include/KHR/khrplatform.h src/gl.c)
else()
	message(STATUS "Static Build")
	add_library(${PROJECT_NAME} STATIC include/glad/gl.h include/KHR/khrplatform.h src/gl.c)
endif()

target_include_directories(${PROJECT_NAME} PUBLIC include/)
set_target_properties(${PROJECT_NAME}
	PROPERTIES
	VERSION "2.0.4")

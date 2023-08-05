cmake_minimum_required(VERSION 3.18)
project(Glad2)

message ("  - Glad2 -")

if (SHARED_BUILD)
	message(STATUS "Shared Build")
	if (MSVC)
		add_library(${PROJECT_NAME} STATIC include/glad/gl.h include/KHR/khrplatform.h src/gl.c)
	else()
		add_library(${PROJECT_NAME} SHARED include/glad/gl.h include/KHR/khrplatform.h src/gl.c)
	endif()
else()
	message(STATUS "Static Build")
	add_library(${PROJECT_NAME} STATIC include/glad/gl.h include/KHR/khrplatform.h src/gl.c)
endif()

target_include_directories(${PROJECT_NAME} PUBLIC include/)

cmake_minimum_required(VERSION 3.18)

message("")
message ("  - Glad2 -")

project(Glad2)

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

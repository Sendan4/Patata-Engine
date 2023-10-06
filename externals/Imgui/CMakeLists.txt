cmake_minimum_required(VERSION 3.18)

project("Imgui" LANGUAGES CXX)

message("")
message("  - Imgui -")

include(CheckIncludeFile)

CHECK_INCLUDE_FILE("stdio.h" HAVE_STDIO_H)
CHECK_INCLUDE_FILE("stdint.h" HAVE_STDINT_H)
CHECK_INCLUDE_FILE("float.h" HAVE_FLOAT_H)
CHECK_INCLUDE_FILE("stdarg.h" HAVE_STDARG_H)
CHECK_INCLUDE_FILE("stddef.h" HAVE_STDDEF_H)
CHECK_INCLUDE_FILE("string.h" HAVE_STRING_H)
CHECK_INCLUDE_FILE("assert.h" HAVE_ASSERT_H)
CHECK_INCLUDE_FILE("stdlib.h" HAVE_STDLIB_H)
CHECK_INCLUDE_FILE("limits.h" HAVE_LIMITS_H)
CHECK_INCLUDE_FILE("math.h" HAVE_MATH_H)

if (NOT HAVE_STDIO_H OR NOT HAVE_STDINT_H OR NOT HAVE_FLOAT_H OR NOT HAVE_STDARG_H OR NOT HAVE_STDDEF_H OR NOT HAVE_STRING_H OR NOT HAVE_ASSERT_H OR NOT HAVE_STDLIB_H OR NOT HAVE_LIMITS_H OR NOT HAVE_MATH_H)
	message(FATAL_ERROR "include files missing")
endif()

if (SHARED_BUILD)
	message(STATUS "Shared Build")
	add_library(${PROJECT_NAME} SHARED)
else ()
	message(STATUS "Static Build")
	add_library(${PROJECT_NAME} STATIC)
endif()

target_include_directories(${PROJECT_NAME} PUBLIC "imgui/" "imgui/backends")

target_sources(${PROJECT_NAME} PRIVATE
	"imgui/imgui.cpp"
	"imgui/imgui_demo.cpp"
	"imgui/imgui_draw.cpp"
	"imgui/imgui_tables.cpp"
	"imgui/imgui_widgets.cpp")

if (${Vulkan_FOUND})
	message(STATUS "Backend: Vulkan")
	target_sources(${PROJECT_NAME} PRIVATE
		"imgui/backends/imgui_impl_vulkan.cpp")
endif()

message(STATUS "Backend: SDL2, OpenGL3")
target_sources(${PROJECT_NAME} PRIVATE
	"imgui/backends/imgui_impl_sdl2.cpp"
	"imgui/backends/imgui_impl_opengl3.cpp")

if (USE_EXTERNAL_LIBS)
	# Linux or MSVC
	if (MSVC OR LINUX OR CMAKE_SYSTEM_NAME STREQUAL "Linux")
		target_link_libraries(${PROJECT_NAME} PRIVATE vulkan)
	endif()

	# MSYS2 Vulkan Link
	if (NOT MSVC AND (WIN32 OR CMAKE_SYSTEM_NAME STREQUAL "Windows"))
		target_link_libraries(${PROJECT_NAME} PRIVATE
			-lvulkan-1
			-L${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
	endif()

	if (SHARED_BUILD)
		target_link_libraries(${PROJECT_NAME} PRIVATE SDL2main SDL2::SDL2)
	else()
		target_link_libraries(${PROJECT_NAME} PRIVATE SDL2main SDL2-static)

		if (NOT MSVC)
				if ((WIN32 OR CMAKE_SYSTEM_NAME STREQUAL "Windows") OR (LINUX OR CMAKE_SYSTEM_NAME STREQUAL "Linux"))
					target_link_libraries(${PROJECT_NAME} PRIVATE -static-libgcc -static-libstdc++)
				endif()
		endif()
	endif()
else()
	# Package Mananger
	target_link_libraries(${PROJECT_NAME} PRIVATE
		${Vulkan_LIBRARIES}
		${SDL2_LIBRARIES})
endif()

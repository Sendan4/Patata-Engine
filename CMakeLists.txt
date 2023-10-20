cmake_minimum_required(VERSION 3.18)

message("")
message("  - Patata Engine -")

option(SHARED_BUILD "Static Or Shared library" ON)
option(USE_EXTERNAL_LIBS OFF)
option(USE_GIT "Grab git information" ON)
option(USE_CUSTOM_ICON OFF)
option(ENABLE_ICON "Use icon in runtime" ON)

if (MSVC)
	set(CMAKE_SKIP_INSTALL_RULES YES)
endif()

if (NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release)
endif()

project("PatataEngine")

enable_language(CXX)
include(CheckIncludeFiles)
include(CheckCXXCompilerFlag)
include(CheckIncludeFileCXX)
if (WIN32 OR CMAKE_SYSTEM_NAME STREQUAL "Windows")
	enable_language(C)
	include(CheckIncludeFile)
endif()

if (NOT MSVC)
	check_cxx_compiler_flag("-std=c++20" COMPILER_SUPPORTS_CXX20)

	check_cxx_compiler_flag("-Wextra" COMPILER_SUPPORTS_WEXTRA)
	check_cxx_compiler_flag("-Wall" COMPILER_SUPPORTS_WALL)

	if (COMPILER_SUPPORTS_CXX20)
		set(CMAKE_CXX_STANDARD 20)
		set(CMAKE_CXX_STANDARD_REQUIRED ON)
	else()
    	message(FATAL_ERROR "The compiler does not support the C++20 standard")
	endif()

else()
	check_cxx_compiler_flag("/std:c++20" COMPILER_SUPPORTS_CXX20)
	check_cxx_compiler_flag("/Wall" COMPILER_SUPPORTS_WALL)

	if (COMPILER_SUPPORTS_CXX20)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++20")
	else()
    	message(FATAL_ERROR "The compiler does not support the C++20 standard")
	endif()
endif()

CHECK_INCLUDE_FILE_CXX("cstdint" HAVE_CSTDINT [LANGUAGE CXX])
CHECK_INCLUDE_FILE_CXX("cstring" HAVE_CSTRING [LANGUAGE CXX])
CHECK_INCLUDE_FILE_CXX("algorithm" HAVE_IOSTREAM [LANGUAGE CXX])
CHECK_INCLUDE_FILE_CXX("vector" HAVE_VECTOR [LANGUAGE CXX])
CHECK_INCLUDE_FILE_CXX("tuple" HAVE_TUPLE [LANGUAGE CXX])

if (WIN32 OR CMAKE_SYSTEM_NAME STREQUAL "Windows")
	CHECK_INCLUDE_FILE("windows.h" HAVE_WINDOWS_H)
endif()

if (NOT HAVE_CSTDINT OR NOT HAVE_CSTRING OR NOT HAVE_IOSTREAM OR NOT HAVE_VECTOR OR NOT HAVE_TUPLE)
	if (NOT HAVE_WINDOWS_H AND (WIN32 OR CMAKE_SYSTEM_NAME STREQUAL "Windows"))
		message(FATAL_ERROR "include files missing")
	endif()

	message(FATAL_ERROR "include files missing")
endif()

if (USE_GIT)
	set (GIT_BRANCH "NULL")
	set (GIT_HASH_SHORT "0")
	set (GIT_HASH_LONG "0")

	# Git Macros
	execute_process(
		COMMAND git branch --show-current
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
		OUTPUT_VARIABLE GIT_BRANCH
		OUTPUT_STRIP_TRAILING_WHITESPACE)

	message(STATUS "Git Branch: ${GIT_BRANCH}")

	execute_process(
		COMMAND git rev-parse HEAD
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
		OUTPUT_VARIABLE GIT_HASH_LONG
		OUTPUT_STRIP_TRAILING_WHITESPACE)

	execute_process(
		COMMAND git rev-parse --short HEAD
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
		OUTPUT_VARIABLE GIT_HASH_SHORT
		OUTPUT_STRIP_TRAILING_WHITESPACE)

	# Macros
	add_compile_definitions(
		PATATA_GIT_BRANCH="${GIT_BRANCH}"
		PATATA_GIT_HASH_LONG="${GIT_HASH_LONG}"
		PATATA_GIT_HASH_SHORT="${GIT_HASH_SHORT}")

endif()

set (build_system "CMake (${CMAKE_GENERATOR})")
get_filename_component(compiler_program ${CMAKE_CXX_COMPILER} NAME)

# Macros
add_compile_definitions(
	PATATA_BUILD_SYSTEM="${build_system}"
	PATATA_VERSION="0"
	PATATA_ENGINE_NAME="Patata Engine"
	PATATA_COMPILER_PROGRAM="${compiler_program}")

if (DEFINED GAME_NAME AND NOT "${GAME_NAME}" STREQUAL "")
	message(STATUS "Game Name: ${GAME_NAME}")
	add_compile_definitions(GAME_NAME="${GAME_NAME}")
endif()

if (ENABLE_ICON)
	message(STATUS "Icon: Yes")
	add_compile_definitions(USE_ICON="1")
	if (USE_CUSTOM_ICON)
		message(STATUS "Custom Icon Path: ${ICON_PATH}")
	endif()
else()
	message(STATUS "Icon: No")
endif()

# Windows shared library
if (SHARED_BUILD)
	add_compile_definitions(SHARED_LIBRARY_EXPORT_DEFINE="1")
	message(STATUS "Shared Build")
else ()
	add_compile_definitions(SHARED_LIBRARY_EXPORT_DEFINE="0")
	message(STATUS "Static Build")
endif()

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

if (${CMAKE_BUILD_TYPE} STREQUAL "Release")
	message(STATUS "Build Type: Release")
	add_compile_definitions(PATATA_BUILD_TYPE="Release")
elseif(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
	message(STATUS "Build Type: Debug")
	add_compile_definitions(
		PATATA_BUILD_TYPE="Debug"
		DEBUG=1)
elseif(${CMAKE_BUILD_TYPE} STREQUAL "RelWithDebInfo")
	message(STATUS "Build Type: Debug Optimized")
	add_compile_definitions(
		PATATA_BUILD_TYPE="Debug Optimized"
		DEBUG=1)
elseif(${CMAKE_BUILD_TYPE} STREQUAL "MinSizeRel")
	message(STATUS "Build Type: Minimal Size Release")
	add_compile_definitions(PATATA_BUILD_TYPE="Minimal Size Release")
endif()

if (NOT USE_EXTERNAL_LIBS)
	# Package Mananger
	add_subdirectory(externals/fast_io)
	find_package(yaml-cpp REQUIRED)
	find_package(Vulkan REQUIRED)
	add_subdirectory(externals/Glad2)
	find_package(SDL2 REQUIRED)

	if (${CMAKE_BUILD_TYPE} STREQUAL "Debug" OR ${CMAKE_BUILD_TYPE} STREQUAL "RelWithDebInfo")
		add_subdirectory(externals/Imgui)

		find_file(HAVE_IMGUI_VULKAN_H "imgui_impl_vulkan.h" PATHS "${CMAKE_CURRENT_SOURCE_DIR}/externals/Imgui/imgui/backends")
		find_file(HAVE_IMGUI_SDL2_H "imgui_impl_sdl2.h" PATHS "${CMAKE_CURRENT_SOURCE_DIR}/externals/Imgui/imgui/backends")
		find_file(HAVE_IMGUI_OPENGL3_H "imgui_impl_opengl3.h" PATHS "${CMAKE_CURRENT_SOURCE_DIR}/externals/Imgui/imgui/backends")

		if (NOT HAVE_IMGUI_VULKAN_H OR NOT HAVE_IMGUI_SDL2_H OR NOT HAVE_IMGUI_OPENGL3_H)
			message(FATAL_ERROR "Missing Headers")
		endif()
	endif()

	find_file(HAVE_VULKAN_HPP "vulkan/vulkan.hpp" PATHS ${Vulkan_INCLUDE_DIRS})
	find_file(HAVE_SDL_H "SDL.h" PATHS ${SDL2_INCLUDE_DIRS})
	find_file(HAVE_SDL_VULKAN_H "SDL_vulkan.h" PATHS ${SDL2_INCLUDE_DIRS})
	find_file(HAVE_SDL_OPENGL_H "SDL_opengl.h" PATHS ${SDL2_INCLUDE_DIRS})
	find_file(HAVE_YAML_CPP_H "yaml-cpp/yaml.h" PATHS ${Yaml-cpp_INCLUDE_DIRS})

	message("")
	message("  - Patata Engine -")

	if (NOT HAVE_SDL_H OR NOT HAVE_SDL_VULKAN_H OR NOT HAVE_SDL_OPENGL_H OR NOT HAVE_VULKAN_HPP OR NOT HAVE_YAML_CPP_H)
		message(FATAL_ERROR "Missing Headers")
	else()
		if (HAVE_VULKAN_HPP)
			message(STATUS "Looking for vulkan/vulkan.hpp - found")
		endif()

		if (HAVE_SDL_H)
			message(STATUS "Looking for SDL.h - found")
		endif()

		if (HAVE_SDL_VULKAN_H)
			message(STATUS "Looking for SDL_vulkan.h - found")
		endif()

		if (HAVE_SDL_OPENGL_H)
			message(STATUS "Looking for SDL_opengl.h - found")
		endif()

		if (HAVE_YAML_CPP_H)
			message(STATUS "Looking for yaml-cpp/yaml.h - found")
		endif()

		if (HAVE_IMGUI_VULKAN_H)
			message(STATUS "Looking for imgui_impl_vulkan.h - found")
		endif()

		if (HAVE_IMGUI_SDL2_H)
			message(STATUS "Looking for imgui_impl_sdl2.h - found")
		endif()

		if (HAVE_IMGUI_OPENGL3_H)
			message(STATUS "Looking for imgui_impl_opengl3.h - found")
		endif()
	endif()
else()
	# using submodules
	add_subdirectory(externals)
endif()

# Glad Check
find_file(HAVE_GL_H "glad/gl.h" PATHS "${CMAKE_CURRENT_SOURCE_DIR}/externals/Glad2/include/")

if (NOT HAVE_GL_H)
	message(FATAL_ERROR "Missing Headers")
else()
	if (HAVE_SDL_H)
		message(STATUS "Looking for glad/gl.h - found")
	endif()
endif()

add_subdirectory(data)
add_subdirectory(data/assets)

# Library
include_directories(include/)
add_subdirectory(src)

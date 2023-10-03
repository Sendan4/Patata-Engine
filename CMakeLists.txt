cmake_minimum_required(VERSION 3.18)

message("")
message("  - Patata Engine -")

option(SHARED_BUILD "Static Or Shared library" ON)
option(USE_EXTERNAL_LIBS OFF)
option(USE_GIT OFF)
option(USE_CUSTOM_ICON OFF)
option(ENABLE_ICON "Use icon in runtime" ON)

if (NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release)
endif()

project("PatataEngine")

enable_language(CXX)
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
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")
	else()
    	message(FATAL_ERROR "The compiler does not support the C++20 standard")
	endif()

	if (COMPILER_SUPPORTS_WEXTRA AND COMPILER_SUPPORTS_WALL)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_CLAGS} -Wall -Wextra")
	elseif (COMPILER_SUPPORTS_WALL AND NOT COMPILER_SUPPORTS_WEXTRA)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_CLAGS} -Wall")
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

CHECK_INCLUDE_FILE_CXX("iostream" HAVE_IOSTREAM [LANGUAGE CXX])
CHECK_INCLUDE_FILE_CXX("ios" HAVE_IOS [LANGUAGE CXX])
CHECK_INCLUDE_FILE_CXX("iomanip" HAVE_IOMANIP [LANGUAGE CXX])
CHECK_INCLUDE_FILE_CXX("cstdint" HAVE_CSTDINT [LANGUAGE CXX])
CHECK_INCLUDE_FILE_CXX("cstring" HAVE_CSTRING [LANGUAGE CXX])
CHECK_INCLUDE_FILE_CXX("algorithm" HAVE_IOSTREAM [LANGUAGE CXX])
CHECK_INCLUDE_FILE_CXX("vector" HAVE_VECTOR [LANGUAGE CXX])

if (WIN32 OR CMAKE_SYSTEM_NAME STREQUAL "Windows")
	CHECK_INCLUDE_FILE("windows.h" HAVE_WINDOWS_H)
endif()

if (NOT HAVE_CSTDINT OR NOT HAVE_CSTRING OR NOT HAVE_IOSTREAM OR NOT HAVE_IOS OR NOT HAVE_IOMANIP OR NOT HAVE_IOSTREAM OR NOT HAVE_VECTOR)
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
		WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
		OUTPUT_VARIABLE GIT_BRANCH
		OUTPUT_STRIP_TRAILING_WHITESPACE)

	message(STATUS "Git Branch: ${GIT_BRANCH}")

	execute_process(
		COMMAND git rev-parse HEAD
		WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
		OUTPUT_VARIABLE GIT_HASH_LONG
		OUTPUT_STRIP_TRAILING_WHITESPACE)

	execute_process(
		COMMAND git rev-parse --short HEAD
		WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
		OUTPUT_VARIABLE GIT_HASH_SHORT
		OUTPUT_STRIP_TRAILING_WHITESPACE)

	# Macros
	add_compile_definitions(
		GIT_BRANCH="${GIT_BRANCH}"
		GIT_HASH_LONG="${GIT_HASH_LONG}"
		GIT_HASH_SHORT="${GIT_HASH_SHORT}")

endif()
# Macros
add_compile_definitions(
	BUILDSYS="CMake"
	PATATAVERSION="0"
	ENGINE_NAME="Patata Engine")

if (DEFINED GAME_NAME AND NOT "${GAME_NAME}" STREQUAL "")
	add_compile_definitions(GAME_NAME="${GAME_NAME}")
endif()

if (ENABLE_ICON)
	message(STATUS "Icon: Yes")
	add_compile_definitions(USE_ICON="1")
	if (USE_CUSTOM_ICON)
		message(STATUS "Custom Icon Path: ${ICON_PATH}")
		message(STATUS "Custom Icon: Found")
	else()
		message(STATUS "Custom Icon: Not Found")
	endif()
else()
	message(STATUS "Icon: No")
endif()

message(STATUS "Game Name: ${GAME_NAME}")

# Windows shared library
if (SHARED_BUILD AND (WIN32 OR CMAKE_SYSTEM_NAME STREQUAL "Windows"))
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
	add_compile_definitions(BUILD_TYPE="Release")
elseif(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
	message(STATUS "Build Type: Debug")
	add_compile_definitions(
		BUILD_TYPE="Debug"
		DEBUG=1)
elseif(${CMAKE_BUILD_TYPE} STREQUAL "RelWithDebInfo")
	message(STATUS "Build Type: Debug Optimized")
	add_compile_definitions(
		BUILD_TYPE="Debug Optimized"
		DEBUG=1)
elseif(${CMAKE_BUILD_TYPE} STREQUAL "MinSizeRel")
	message(STATUS "Build Type: Minimal Size Release")
	add_compile_definitions(BUILD_TYPE="Minimal Size Release")
endif()

if (NOT USE_EXTERNAL_LIBS)
	find_package(yaml-cpp REQUIRED)
	find_package(Vulkan REQUIRED)
	add_subdirectory(externals/Glad2)
	find_package(SDL2 REQUIRED)

	if (${CMAKE_BUILD_TYPE} STREQUAL "Debug" OR ${CMAKE_BUILD_TYPE} STREQUAL "RelWithDebInfo")
		add_subdirectory(externals/imgui)
	endif()
else()
	add_subdirectory(externals)
endif()

# Copy Files
if (MSVC)
	if (${CMAKE_BUILD_TYPE} STREQUAL "Debug" OR ${CMAKE_BUILD_TYPE} STREQUAL "RelWithDebInfo")
		file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/patata.yaml" "${CMAKE_CURRENT_SOURCE_DIR}/LICENSES"
			DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/Release)

		if (DEFINED GAME_NAME AND NOT "${GAME_NAME}" STREQUAL "")
			file(RENAME "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release/patata.yaml" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release/${GAME_NAME}.yaml")
		endif()
	else()
		file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/patata.yaml" "${CMAKE_CURRENT_SOURCE_DIR}/LICENSES"
			DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/${CMAKE_BUILD_TYPE})

		if (DEFINED GAME_NAME AND NOT "${GAME_NAME}" STREQUAL "")
			file(RENAME "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_BUILD_TYPE}/patata.yaml" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_BUILD_TYPE}/${GAME_NAME}.yaml")
		endif()
	endif()
else ()
	file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/patata.yaml" "${CMAKE_CURRENT_SOURCE_DIR}/LICENSES"
		DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

	if (DEFINED GAME_NAME AND NOT "${GAME_NAME}" STREQUAL "")
		file(RENAME "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/patata.yaml" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${GAME_NAME}.yaml")
	endif()
endif ()

# Library
include_directories(include/)
add_subdirectory(src)
add_subdirectory(assets)

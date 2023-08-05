cmake_minimum_required(VERSION 3.18)

option(SHARED_BUILD ON)
option(USE_EXTERNAL_LIBS OFF)

if (NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release)
endif()

message("  - Patata Engine -")

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
	project("Patata_Engine" LANGUAGES CXX RC)
else()
	project("Patata_Engine" LANGUAGES CXX)
endif()

if (NOT MSVC)
	include(CheckCXXCompilerFlag)
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
endif()

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
	BUILDSYS="CMake"
	PATATAVERSION="0"
	GIT_BRANCH="${GIT_BRANCH}"
	GIT_HASH_LONG="${GIT_HASH_LONG}"
	GIT_HASH_SHORT="${GIT_HASH_SHORT}"
)

if (${CMAKE_BUILD_TYPE} STREQUAL "Release")
	add_compile_definitions(BUILD_TYPE="Release")
elseif(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
	add_compile_definitions(
		BUILD_TYPE="Debug"
		DEBUG=1)
elseif(${CMAKE_BUILD_TYPE} STREQUAL "RelWithDebInfo")
	add_compile_definitions(
		BUILD_TYPE="Debug Optimized"
		DEBUG=1)
elseif(${CMAKE_BUILD_TYPE} STREQUAL "MinSizeRel")
	add_compile_definitions(BUILD_TYPE="Minimal Size Release")
endif()

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

if (NOT USE_EXTERNAL_LIBS)
	find_package(Vulkan REQUIRED)
	add_subdirectory(externals/Glad2)
	find_package(SDL2 REQUIRED)
else()
	add_subdirectory(externals)

	message(STATUS "Vulkan-Headers Directory: ${CMAKE_SOURCE_DIR}/externals/Vulkan-Headers/include")
	include_directories("${CMAKE_SOURCE_DIR}/externals/Vulkan-Headers/include")
endif()

# Executable
add_subdirectory(src)

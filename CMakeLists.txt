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

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

execute_process(
	COMMAND git branch --show-current
	WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
	OUTPUT_VARIABLE GIT_BRANCH
	OUTPUT_STRIP_TRAILING_WHITESPACE)

message(STATUS "Git Branch: ${GIT_BRANCH}")

# Macros
add_definitions(
	-DBuildSys="CMake"
	-DPatataVersion="0"
	-DGIT_BRANCH="${GIT_BRANCH}"
)

set(CXX_STANDARD_REQUIRED true)
set(CMAKE_CXX_STANDARD 20)

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

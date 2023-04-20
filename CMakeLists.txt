cmake_minimum_required(VERSION 3.18)

option(SHARED_BUILD ON)
option(USE_EXTERNAL_LIBS ON)

set(CMAKE_BUILD_TYPE Release)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
	project("Patata_Engine" LANGUAGES CXX RC)
else()
	project("Patata_Engine" LANGUAGES CXX)
endif()

include(CheckCXXCompilerFlag)
check_cxx_compiler_flag("-std=c++20" COMPILER_SUPPORTS_CXX20)

if (NOT MSVC)
	check_cxx_compiler_flag("-Wextra" COMPILER_SUPPORTS_WEXTRA)
	check_cxx_compiler_flag("-Wall" COMPILER_SUPPORTS_WALL)

	if (COMPILER_SUPPORTS_CXX20)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")
	else()
    	message(FATAL_ERROR "El compilador no admite el estándar C++20")
	endif()

	if (COMPILER_SUPPORTS_WEXTRA AND COMPILER_SUPPORTS_WALL)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_CLAGS} -Wall -Wextra")
	elseif (COMPILER_SUPPORTS_WALL AND NOT COMPILER_SUPPORTS_WEXTRA)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_CLAGS} -Wall")
	endif ()
endif()
	
set(CXX_STANDARD_REQUIRED true)

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

if(NOT SHARED_BUILD AND NOT MSVC)
	set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
endif()

set(MAIN_INCLUDE
	"include/Core/Patata_Engine.hpp"
	"include/Core/Log.hpp"
	"include/Core/Window.hpp"
	"include/Core/terminal_colors.hpp"
	"include/Graphics/OpenGL.hpp"
	"include/Graphics/Vulkan.hpp"
	"include/Graphics/API_Graphics_Switch.hpp"
	"include/EngineInfo.hpp")
set(SOURCE
	"src/Core/main.cpp"
	"src/Core/Start_And_End.cpp"
	"src/Core/Main_Loop.cpp"
	"src/Core/API_Graphics_Switch.cpp"
	"src/Window/Window.cpp"
	"src/Window/Window_Icon.cpp"
	"src/Vulkan/Setup_Vulkan.cpp"
	"src/Opengl/Opengl_Context.cpp"
	"src/Log/OpenGL_Info.cpp"
	"src/Log/Mapache.cpp"
	"src/Log/Start_Patata_Log_Info.cpp")

set(icon "src/Core/patata.rc")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

find_package(Vulkan REQUIRED)

add_subdirectory(externals/Glad2)
include_directories("externals/Glad2/include/")
if (NOT USE_EXTERNAL_LIBS)
	find_package(SDL2 REQUIRED)
else()
	if (SHARED_BUILD)
		set(SDL_SHARED_ENABLED_BY_DEFAULT ON)
		set(SDL_STATIC_ENABLED_BY_DEFAULT OFF)
	else ()
		set(SDL_SHARED_ENABLED_BY_DEFAULT OFF)
		set(SDL_STATIC_ENABLED_BY_DEFAULT ON)
	endif ()
	
	add_subdirectory(externals/SDL)
	include_directories("${CMAKE_SOURCE_DIR}/externals/SDL/include")
	
	if (MSVC)
		include_directories("C:/VulkanSDK/1.3.231.1/Include")
	endif()
endif()

include_directories("include/")

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
	add_executable(${PROJECT_NAME}
		${MAIN_INCLUDE}
		${SOURCE}
		"src/Core/patata.rc")
else()
	add_executable(${PROJECT_NAME}
		${MAIN_INCLUDE}
		${SOURCE})
endif()

if (SHARED_BUILD)
	if (USE_EXTERNAL_LIBS)
		target_link_libraries(${PROJECT_NAME} PRIVATE
			glad2
			SDL2main SDL2::SDL2
			${Vulkan_LIBRARIES})
	else()
		target_link_libraries(${PROJECT_NAME} PRIVATE
			glad2
			${SDL2_LIBRARIES}
			${Vulkan_LIBRARIES})
	endif()
else()
	if (USE_EXTERNAL_LIBS)
		target_link_libraries(${PROJECT_NAME} PRIVATE
			glad2
			SDL2main SDL2-static
			${Vulkan_LIBRARIES})
	else()
		target_link_libraries(${PROJECT_NAME} PRIVATE
			glad2
			${SDL2_LIBRARIES}
			${Vulkan_LIBRARIES})
	endif()
endif()

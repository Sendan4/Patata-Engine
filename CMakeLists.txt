cmake_minimum_required(VERSION 3.18)

option(BUILD_TYPE ON)
option(USE_SYSTEM_LIBS ON)

set(CMAKE_BUILD_TYPE Release)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
	project("Patata_Engine" LANGUAGES CXX RC)
else()
	project("Patata_Engine" LANGUAGES CXX)
endif()

if(NOT BUILD_TYPE AND NOT MSVC)
	set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
endif()

set(MAIN_INCLUDE
	"include/sdl.hpp"
	"include/window.hpp"
	"include/API_Graphics_Switch.hpp"
	"include/Events.hpp"
	"include/Opengl_context.hpp"
	"include/Vulkan.hpp")
set(SOURCE
	"src/base/Core/main.cpp"
	"src/base/Core/sdl.cpp"
	"src/base/Window/window.cpp"
	"src/base/Core/API_Graphics_Switch.cpp"
	"src/base/Events/Main_events.cpp"
	"src/base/Vulkan/Setup_Vulkan.cpp"
	"src/base/Opengl/Opengl_context.cpp")

set(icon "data/patata_icon.rc")

set(CXX_STANDARD_REQUIRED true)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

find_package(Vulkan REQUIRED)
add_subdirectory(externals/Glad2)

if (USE_SYSTEM_LIBS)
	find_package(SDL2 REQUIRED)
	find_package(SDL2_image REQUIRED)
else()
	add_subdirectory(externals/SDL)
	include_directories("${CMAKE_SOURCE_DIR}/externals/libs/SDL/include")
	add_subdirectory(externals/SDL_image)
endif()

include_directories("include/")

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
	add_executable(${PROJECT_NAME}
		${MAIN_INCLUDE}
		${SOURCE}
		"data/patata_icon.rc")
else()
	add_executable(${PROJECT_NAME}
		${MAIN_INCLUDE}
		${SOURCE})
endif()

if (BUILD_TYPE)
	target_link_libraries(${PROJECT_NAME} PRIVATE
		SDL2main SDL2::SDL2
		${Vulkan_LIBRARIES}
		glad2)
else()
	target_link_libraries(${PROJECT_NAME} PRIVATE
		SDL2main SDL2-static
		${Vulkan_LIBRARIES}
		glad2)
endif()

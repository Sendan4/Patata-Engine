cmake_minimum_required(VERSION 3.18)
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

set(MAIN_INCLUDE
	"include/sdl.hpp"
	"include/window.hpp"
	"include/API_Graphics_Switch.hpp"
	"include/Events.hpp"
	"include/Opengl_context.hpp"
	"include/Vulkan.hpp"
	"include/terminal_colors.hpp")
set(SOURCE
	"src/base/Core/main.cpp"
	"src/base/Core/sdl.cpp"
	"src/base/Window/window.cpp"
	"src/base/Core/API_Graphics_Switch.cpp"
	"src/base/Events/Main_events.cpp"
	"src/base/Vulkan/Setup_Vulkan.cpp"
	"src/base/Opengl/Opengl_context.cpp")

set(icon "data/patata_icon.rc")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

set(SHARED_BUILD on)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(Vulkan REQUIRED)
add_subdirectory(externals/libs/glad)

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

target_link_libraries(${PROJECT_NAME} PUBLIC
	${SDL2_LIBRARIES}
	${SDL2_image_LIBRARIES}
	${Vulkan_LIBRARIES}
	glad)

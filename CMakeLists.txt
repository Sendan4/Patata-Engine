cmake_minimum_required(VERSION 3.18)

set(CMAKE_BUILD_TYPE Release)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
	project("Patata_Engine" LANGUAGES CXX RC)
else()
	project("Patata_Engine" LANGUAGES CXX)
endif()

set(MAIN_INCLUDE
	"include/init.hpp"
	"include/window.hpp"
	"include/init_graphics_switcher.hpp"
	"include/Events.hpp"
	"include/Opengl_context.hpp")
set(SOURCE
	"src/base/Core/main.cpp"
	"src/base/Core/init_sdl.cpp"
	"src/base/Window/window.cpp"
	"src/base/Core/init_graphics_switcher.cpp"
	"src/base/Events/Main_events.cpp"
	"src/base/Opengl/Opengl_context.cpp")

set(icon "data/patata_icon.rc")

set(CXX_STANDARD_REQUIRED true)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

set(SHARED_BUILD on)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
add_subdirectory(libs/glad)

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

target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_LIBRARIES} SDL2_image::SDL2_image glad)

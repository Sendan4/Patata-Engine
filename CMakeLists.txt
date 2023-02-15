cmake_minimum_required(VERSION 3.18)

set(CMAKE_BUILD_TYPE Release)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
	project("Patata_Engine" LANGUAGES CXX RC)
else()
	project("Patata_Engine" LANGUAGES CXX)
endif()

set(base_dir "src/base")

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
		"${base_dir}/core/main.cpp"
		"include/init.hpp"
		"${base_dir}/core/init_sdl.cpp"
		"include/window.hpp"
		"${base_dir}/window/window.cpp"
		"include/Events.hpp"
		"${base_dir}/events/Main_events.cpp"
		"data/patata_icon.rc")
else()
	add_executable(${PROJECT_NAME}
		"${base_dir}/core/main.cpp"
		"include/init.hpp"
		"${base_dir}/core/init_sdl.cpp"
		"include/window.hpp"
		"${base_dir}/window/window.cpp"
		"include/Events.hpp"
		"${base_dir}/events/Main_events.cpp")
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_LIBRARIES} SDL2_image::SDL2_image glad)

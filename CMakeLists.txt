cmake_minimum_required(VERSION 3.18)

set(CMAKE_BUILD_TYPE Release)
project("Patata_Engine" LANGUAGES CXX)

set(base_dir "src/base")

set(CXX_STANDARD_REQUIRED true)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

find_package(SDL2 REQUIRED)

include_directories("include/")

add_executable(${PROJECT_NAME}
    "${base_dir}/core/main.cpp"
	"include/init.hpp"
    "${base_dir}/core/init_sdl.cpp"
	"include/window.hpp"
	"${base_dir}/window/window.cpp"
	"include/GameMainLoop.hpp"
	"${base_dir}/core/GameMainLoop.cpp"
	"include/Events.hpp"
	"${base_dir}/events/Main_events.cpp")

target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_LIBRARIES})

cmake_minimum_required(VERSION 3.18)
project("Patata_Engine" LANGUAGES CXX)

set(core_dir "src/base/core")
set(window_dir "src/base/window")
set(opengl_dir "src/base/opengl")

set(CXX_STANDARD_REQUIRED true)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

find_package(SDL2 REQUIRED)

include_directories("include/")

add_executable(${PROJECT_NAME}
    "${core_dir}/main.cpp"
	"include/init.hpp"
    "${core_dir}/init_sdl.cpp"
	"include/window.hpp"
	"${window_dir}/window.cpp")

target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_LIBRARIES})

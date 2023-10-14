cmake_minimum_required(VERSION 3.18)

project("Game" LANGUAGES CXX)

add_subdirectory(subprojects/Patata-Engine/)

# fix SDL_config.h
include_directories(subprojects/Patata-Engine/externals/SDL/include)
# ----

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_executable(${PROJECT_NAME} "Main.cpp")

target_include_directories(${PROJECT_NAME} PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}/subprojects/Patata-Engine/include"
	"${CMAKE_CURRENT_SOURCE_DIR}/subprojects/Patata-Engine/externals/Vulkan-Headers/include")
target_link_libraries(${PROJECT_NAME} PRIVATE PatataEngine)

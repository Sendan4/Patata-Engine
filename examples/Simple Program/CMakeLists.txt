cmake_minimum_required(VERSION 3.18)

project("Example" LANGUAGES CXX)

add_subdirectory(subprojects/patata-engine/)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_executable(${PROJECT_NAME} "Main.cpp")

target_include_directories(${PROJECT_NAME} PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}/subprojects/patata-engine/include"
	"${CMAKE_CURRENT_SOURCE_DIR}/subprojects/patata-engine/externals/SDL/include")

target_link_libraries(${PROJECT_NAME} PRIVATE PatataEngine)

if (LIBS_SHARED_BUILD)
	target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2)
endif()

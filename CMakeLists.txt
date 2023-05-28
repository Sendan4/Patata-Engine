cmake_minimum_required(VERSION 3.18)

option(SHARED_BUILD ON)
option(USE_EXTERNAL_LIBS ON)

set(CMAKE_BUILD_TYPE Release)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
	project("Patata_Engine" LANGUAGES CXX RC)
else()
	project("Patata_Engine" LANGUAGES CXX)
endif()

if(NOT SHARED_BUILD AND NOT MSVC)
	set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
endif()

set(MAIN_INCLUDE
	"include/Core/sdl.hpp"
	"include/Core/window.hpp"
	"include/Core/Events.hpp"
	"include/Graphics/Opengl_context.hpp"
	"include/Graphics/Vulkan.hpp"
	"include/Graphics/API_Graphics_Switch.hpp"
	"include/EngineInfo.hpp")
set(SOURCE
	"src/base/Core/main.cpp"
	"src/base/Core/sdl.cpp"
	"src/base/Window/window.cpp"
	"src/base/Window/window_icon.cpp"
	"src/base/Core/API_Graphics_Switch.cpp"
	"src/base/Events/Main_events.cpp"
	"src/base/Vulkan/Setup_Vulkan.cpp"
	"src/base/Opengl/Opengl_context.cpp")

set(icon "src/base/Core/patata.rc")

set(CXX_STANDARD_REQUIRED true)
set(CMAKE_CXX_STANDARD 20)
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
		"src/base/Core/patata.rc")
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

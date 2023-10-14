# Externals / Thrid Party Libraries

# Yaml-cpp
message("")
message("  - Yaml-cpp -")

set (YAML_CPP_BUILD_TOOLS OFF)
set (YAML_CPP_INSTALL OFF)
set (YAML_CPP_BUILD_TESTS OFF)

if (SHARED_BUILD)
	set (YAML_BUILD_SHARED_LIBS ON)
	message(STATUS "Shared Build")
else ()
	message(STATUS "Static Build")
endif()

add_subdirectory(yaml-cpp)

if (MSVC OR LINUX)
	# Vulkan Validation Layer
	if (${CMAKE_BUILD_TYPE} STREQUAL "Debug" OR ${CMAKE_BUILD_TYPE} STREQUAL "RelWithDebInfo")
		message("")
		message("  - Vulkan ValidationLayers -")
		set (UPDATE_DEPS ON)
		add_subdirectory(Vulkan-ValidationLayers)
	endif()

	# Vulkan
	message("")
	message("  - Vulkan Loader -")
	set (UPDATE_DEPS ON)
	add_subdirectory(Vulkan-Loader)
endif()

# Glad2
add_subdirectory(Glad2)

# SDL2
message("")
message("  - SDL2 -")

if (NOT SHARED_BUILD)
	set(SDL_SHARED OFF)
	set(SDL_STATIC ON)
else ()
	set(SDL_SHARED ON)
	set(SDL_STATIC OFF)
endif ()
set(SDL_TEST OFF)
set (SDL_DIRECTX OFF)
set (SDL_RENDER_D3D OFF)

add_subdirectory(SDL)

if (${CMAKE_BUILD_TYPE} STREQUAL "Debug" OR ${CMAKE_BUILD_TYPE} STREQUAL "RelWithDebInfo")
	add_subdirectory(Imgui)
endif()

# checks
message("")
message("  - Patata Engine -")

find_file(HAVE_VULKAN_HPP "vulkan/vulkan.hpp" PATHS "${CMAKE_CURRENT_SOURCE_DIR}/Vulkan-Headers/include/")
find_file(HAVE_SDL_H "SDL.h" PATHS "${CMAKE_CURRENT_SOURCE_DIR}/SDL/include/")
find_file(HAVE_SDL_VULKAN_H "SDL_vulkan.h" PATHS "${CMAKE_CURRENT_SOURCE_DIR}/SDL/include/")
find_file(HAVE_SDL_OPENGL_H "SDL_opengl.h" PATHS "${CMAKE_CURRENT_SOURCE_DIR}/SDL/include/")
find_file(HAVE_YAML_CPP_H "yaml-cpp/yaml.h" PATHS "${CMAKE_BINARY_DIR}/externals/yaml-cpp/include/")

if (${CMAKE_BUILD_TYPE} STREQUAL "Debug" OR ${CMAKE_BUILD_TYPE} STREQUAL "RelWithDebInfo")
	find_file(HAVE_IMGUI_VULKAN_H "imgui_impl_vulkan.h" PATHS "${CMAKE_CURRENT_SOURCE_DIR}/Imgui/imgui/backends")
	find_file(HAVE_IMGUI_SDL2_H "imgui_impl_sdl2.h" PATHS "${CMAKE_CURRENT_SOURCE_DIR}/Imgui/imgui/backends")
	find_file(HAVE_IMGUI_OPENGL3_H "imgui_impl_opengl3.h" PATHS "${CMAKE_CURRENT_SOURCE_DIR}/Imgui/imgui/backends")
endif()

if (NOT HAVE_SDL_H OR NOT HAVE_SDL_VULKAN_H OR NOT HAVE_SDL_OPENGL_H OR NOT HAVE_VULKAN_HPP OR NOT HAVE_YAML_CPP_H)
	message(FATAL_ERROR "Missing Headers")
else()
	if (HAVE_VULKAN_HPP)
		message(STATUS "Looking for vulkan/vulkan.hpp - found")
	endif()

	if (HAVE_SDL_H)
		message(STATUS "Looking for SDL.h - found")
	endif()

	if (HAVE_SDL_VULKAN_H)
		message(STATUS "Looking for SDL_vulkan.h - found")
	endif()

	if (HAVE_SDL_OPENGL_H)
		message(STATUS "Looking for SDL_opengl.h - found")
	endif()

	if (HAVE_YAML_CPP_H)
		message(STATUS "Looking for yaml-cpp/yaml.h - found")
	endif()
endif()

if (${CMAKE_BUILD_TYPE} STREQUAL "Debug" OR ${CMAKE_BUILD_TYPE} STREQUAL "RelWithDebInfo")
	if (NOT HAVE_IMGUI_VULKAN_H OR NOT HAVE_IMGUI_SDL2_H OR NOT HAVE_IMGUI_OPENGL3_H)
		message(FATAL_ERROR "Missing Headers")
	else()
		if (HAVE_IMGUI_VULKAN_H)
			message(STATUS "Looking for imgui_impl_vulkan.h - found")
		endif()

		if (HAVE_IMGUI_SDL2_H)
			message(STATUS "Looking for imgui_impl_sdl2.h - found")
		endif()

		if (HAVE_IMGUI_OPENGL3_H)
			message(STATUS "Looking for imgui_impl_opengl3.h - found")
		endif()
	endif()
endif()

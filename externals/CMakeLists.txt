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

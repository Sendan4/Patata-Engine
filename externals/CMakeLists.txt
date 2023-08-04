# Externals / Thrid Party Libraries

# Vulkan
if (MSVC OR LINUX)
	message("  - Vulkan Loader -")
	set (UPDATE_DEPS ON)
	add_subdirectory(Vulkan-Loader)
endif()

# Vulkan Validation Layer
if (NOT MSVC AND LINUX AND ${CMAKE_BUILD_TYPE} STREQUAL "Debug" OR ${CMAKE_BUILD_TYPE} STREQUAL "RelWithDebInfo")
	message("  - Vulkan ValidationLayers -")
	set (UPDATE_DEPS ON)
	add_subdirectory(Vulkan-ValidationLayers)
endif()


# Glad2
add_subdirectory(Glad2)

# SDL2
message("  - SDL2 -")

if (NOT SHARED_BUILD)
	set(SDL_SHARED OFF)
	set(SDL_STATIC ON)
else ()
	set(SDL_SHARED ON)
	set(SDL_STATIC OFF)
endif ()
set(SDL_TEST OFF)

add_subdirectory(SDL)

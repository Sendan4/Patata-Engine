cmake_minimum_required(VERSION 3.18)

project("Imgui" LANGUAGES CXX VERSION 1.89.9)

message("")
message("  - Imgui -")

include(CheckIncludeFile)

CHECK_INCLUDE_FILE("stdio.h" HAVE_STDIO_H)
CHECK_INCLUDE_FILE("stdint.h" HAVE_STDINT_H)
CHECK_INCLUDE_FILE("float.h" HAVE_FLOAT_H)
CHECK_INCLUDE_FILE("stdarg.h" HAVE_STDARG_H)
CHECK_INCLUDE_FILE("stddef.h" HAVE_STDDEF_H)
CHECK_INCLUDE_FILE("string.h" HAVE_STRING_H)
CHECK_INCLUDE_FILE("assert.h" HAVE_ASSERT_H)
CHECK_INCLUDE_FILE("stdlib.h" HAVE_STDLIB_H)
CHECK_INCLUDE_FILE("limits.h" HAVE_LIMITS_H)
CHECK_INCLUDE_FILE("math.h" HAVE_MATH_H)
find_file(HAVE_IMGUI_VULKAN_H "imgui_impl_vulkan.h" PATHS "${CMAKE_CURRENT_SOURCE_DIR}/backends/")
find_file(HAVE_IMGUI_SDL2_H "imgui_impl_sdl2.h" PATHS "${CMAKE_CURRENT_SOURCE_DIR}/backends/")
find_file(HAVE_IMGUI_OPENGL3_H "imgui_impl_opengl3.h" PATHS "${CMAKE_CURRENT_SOURCE_DIR}/backends/")
find_file(HAVE_IMGUI_H "imgui.h" PATHS "${CMAKE_CURRENT_SOURCE_DIR}/")
find_file(HAVE_IMCONFIG_H "imconfig.h" PATHS "${CMAKE_CURRENT_SOURCE_DIR}/")
find_file(HAVE_IMGUI_INTERNAL_H "imgui_internal.h" PATHS "${CMAKE_CURRENT_SOURCE_DIR}/")
find_file(HAVE_IMSTB_RECTPACK_H "imstb_rectpack.h" PATHS "${CMAKE_CURRENT_SOURCE_DIR}/")
find_file(HAVE_IMSTB_TEXTEDIT_H "imstb_textedit.h" PATHS "${CMAKE_CURRENT_SOURCE_DIR}/")
find_file(HAVE_IMSTB_TRUETYPE_H "imstb_truetype.h" PATHS "${CMAKE_CURRENT_SOURCE_DIR}/")

if (NOT USE_EXTERNAL_LIBS)
	find_file(HAVE_VULKAN_H "vulkan/vulkan.h" PATHS ${Vulkan_INCLUDE_DIRS})
else()
	find_file(HAVE_VULKAN_H "vulkan/vulkan.h" PATHS "${CMAKE_CURRENT_SOURCE_DIR}/../Vulkan-Headers/include/")
endif()

if (NOT HAVE_STDIO_H OR NOT HAVE_STDINT_H OR NOT HAVE_FLOAT_H OR NOT HAVE_STDARG_H OR NOT HAVE_STDDEF_H OR NOT HAVE_STRING_H OR NOT HAVE_ASSERT_H OR NOT HAVE_STDLIB_H OR NOT HAVE_LIMITS_H OR NOT HAVE_MATH_H OR NOT HAVE_IMGUI_VULKAN_H OR NOT HAVE_IMGUI_SDL2_H OR NOT HAVE_IMGUI_OPENGL3_H OR NOT HAVE_VULKAN_H OR NOT HAVE_IMGUI_INTERNAL_H OR NOT HAVE_IMSTB_RECTPACK_H OR NOT HAVE_IMSTB_TEXTEDIT_H OR NOT HAVE_IMSTB_TRUETYPE_H)
	message(FATAL_ERROR "include files missing")
else()
	if (HAVE_IMGUI_H)
		message(STATUS "Looking for imgui.h - found")
	endif()

	if (HAVE_IMGUI_INTERNAL_H)
		message(STATUS "Looking for imgui_internal.h - found")
	endif()

	if (HAVE_IMSTB_RECTPACK_H)
		message(STATUS "Looking for imstb_rectpack.h - found")
	endif()

	if (HAVE_IMSTB_TEXTEDIT_H)
		message(STATUS "Looking for imstb_textedit.h - found")
	endif()

	if (HAVE_IMSTB_TRUETYPE_H)
		message(STATUS "Looking for imstb_truetype.h - found")
	endif()

	if (HAVE_IMGUI_VULKAN_H)
		message(STATUS "Looking for imgui_impl_vulkan.h - found")
	endif()

	if (HAVE_IMGUI_SDL2_H)
		message(STATUS "Looking for imgui_impl_sdl2.h - found")
	endif()

	if (HAVE_IMGUI_OPENGL3_H)
		message(STATUS "Looking for imgui_impl_opengl3.h - found")
	endif()

	if (HAVE_VULKAN_H)
		message(STATUS "Looking for vulkan/vulkan.h - found")
	endif()
endif()

if (SHARED_BUILD AND NOT MSVC)
	message(STATUS "Shared Build")
	add_library(${PROJECT_NAME} SHARED)
else ()
	message(STATUS "Static Build")
	add_library(${PROJECT_NAME} STATIC)
endif()

target_include_directories(${PROJECT_NAME} PUBLIC ".")
target_include_directories(${PROJECT_NAME} PUBLIC "backends/")

if(USE_EXTERNAL_LIBS AND HAVE_VULKAN_H)
	target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../Vulkan-Headers/include/")
endif()

target_sources(${PROJECT_NAME} PRIVATE
	"imgui.cpp"
	"imgui_demo.cpp"
	"imgui_draw.cpp"
	"imgui_tables.cpp"
	"imgui_widgets.cpp")

if ((${Vulkan_FOUND} AND HAVE_VULKAN_H) OR (USE_EXTERNAL_LIBS AND HAVE_VULKAN_H))
	message(STATUS "Backend: Vulkan")
	target_sources(${PROJECT_NAME} PRIVATE
		"backends/imgui_impl_vulkan.cpp")
endif()

message(STATUS "Backend: SDL2, OpenGL3")
target_sources(${PROJECT_NAME} PRIVATE
	"backends/imgui_impl_sdl2.cpp"
	"backends/imgui_impl_opengl3.cpp")

if (USE_EXTERNAL_LIBS)
	# Linux or MSVC
	if (MSVC OR LINUX OR CMAKE_SYSTEM_NAME STREQUAL "Linux")
		target_link_libraries(${PROJECT_NAME} PRIVATE vulkan)
	endif()

	# MSYS2 Vulkan Link
	if (NOT MSVC AND (WIN32 OR CMAKE_SYSTEM_NAME STREQUAL "Windows"))
		target_link_libraries(${PROJECT_NAME} PRIVATE
			-lvulkan-1
			-L${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
	endif()

	if (SHARED_BUILD)
		target_link_libraries(${PROJECT_NAME} PRIVATE SDL2main SDL2::SDL2)
	else()
		target_link_libraries(${PROJECT_NAME} PRIVATE SDL2main SDL2-static)

		if (NOT MSVC)
				if ((WIN32 OR CMAKE_SYSTEM_NAME STREQUAL "Windows") OR (LINUX OR CMAKE_SYSTEM_NAME STREQUAL "Linux"))
					target_link_libraries(${PROJECT_NAME} PRIVATE -static-libgcc -static-libstdc++)
				endif()
		endif()
	endif()
else()
	# Package Mananger
	target_link_libraries(${PROJECT_NAME} PRIVATE
		${Vulkan_LIBRARIES}
		${SDL2_LIBRARIES})
endif()

set_target_properties(${PROJECT_NAME}
	PROPERTIES
	VERSION "1.89.9")

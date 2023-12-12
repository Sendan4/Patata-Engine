file(GLOB_RECURSE Include "${CMAKE_CURRENT_SOURCE_DIR}/../include/PatataEngine/*.hpp")


if (DEFINED SHARED_BUILD AND SHARED_BUILD)
	add_library(${PROJECT_NAME} SHARED)
	add_library(Patata::Engine-Shared ALIAS ${PROJECT_NAME})
endif()

if (DEFINED SHARED_BUILD AND NOT SHARED_BUILD)
	add_library(${PROJECT_NAME} STATIC)
	add_library(Patata::Engine-Static ALIAS ${PROJECT_NAME})
endif()

target_sources (${PROJECT_NAME} PRIVATE
	"Core/Start_And_End.cpp"
	"Core/Input.cpp"
	"Core/Render.cpp"
	"Window/Window.cpp"
	"Vulkan/Setup_Vulkan_Renderer.cpp"
	"Vulkan/Vulkan_Instance.cpp"
	"Vulkan/Vulkan_Logical_And_Queue.cpp"
	"Vulkan/Vulkan_SwapChain.cpp"
	"Vulkan/Vulkan_ImageView.cpp"
	"Vulkan/Vulkan_CommandBuffer.cpp"
	"Vulkan/Vulkan_PipeLine.cpp"
	"Vulkan/Vulkan_RenderPass.cpp"
	"Opengl/OpenGL_Set_ViewPort_And_Resize.cpp"
	"Opengl/OpenGL_Renderer.cpp"
	"Log/Mapache.cpp"
	"Log/ErrorMessages.cpp"
	"Log/YamlErrors.cpp")

if (MSVC)
	# List Headers Files in Visual Studio
	target_sources(${PROJECT_NAME} PRIVATE ${Include})
endif()

if (CMAKE_SYSTEM_NAME STREQUAL "Windows" OR WIN32)
	enable_language(RC)

	target_sources (${PROJECT_NAME} PRIVATE
		"Log/Win/Start_Patata_Log_Info_Win.cpp"
		"Log/Win/WindowLogWin.cpp"
		"Log/Win/Setup_Vulkan_Log_Win.cpp"
		"Log/Win/Vulkan_Info_Win.cpp"
		"Log/Win/OpenGL_Info_Win.cpp"
		"PatataEngine.rc")
else()
	target_sources (${PROJECT_NAME} PRIVATE
		"Log/Start_Patata_Log_Info.cpp"
		"Log/WindowLog.cpp"
		"Log/Setup_Vulkan_Log.cpp"
		"Log/Vulkan_Info.cpp"
		"Log/OpenGL_Info.cpp")
endif()

if (${CMAKE_BUILD_TYPE} STREQUAL "Debug" OR ${CMAKE_BUILD_TYPE} STREQUAL "RelWithDebInfo")
	target_sources(${PROJECT_NAME} PRIVATE
		"ImGUI/ImGUISetupBackend.cpp"
		"ImGUI/ImGUIFrame.cpp"
		"ImGUI/DrawDebugUI.cpp")
endif()

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}../include/")
target_include_directories(${PROJECT_NAME} PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}/"
	"${CMAKE_CURRENT_SOURCE_DIR}Log/")

if (USE_EXTERNAL_LIBS)
	target_include_directories(${PROJECT_NAME} PRIVATE
		"${CMAKE_BINARY_DIR}/externals/SDL/include"
		"${CMAKE_CURRENT_SOURCE_DIR}/../externals/Vulkan-Headers/include")
endif()

target_include_directories(${PROJECT_NAME} PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}/Log/")

# Install With CPack
install(FILES ${Include} DESTINATION "include/PatataEngine/")
install(FILES ${Include_graphics} DESTINATION "include/PatataEngine/Graphics")

install(TARGETS Glad2
	LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
	RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}")

if (${CMAKE_BUILD_TYPE} STREQUAL "Debug" OR ${CMAKE_BUILD_TYPE} STREQUAL "RelWithDebInfo")
	install(TARGETS Imgui
		LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
		RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}")
endif()

if (NOT MSVC)
	if (WIN32 AND NOT MSVC OR MSYS)
		install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/../bin/vulkan-1.dll" DESTINATION "${CMAKE_INSTALL_BINDIR}")
		if (${CMAKE_BUILD_TYPE} STREQUAL "Debug" OR ${CMAKE_BUILD_TYPE} STREQUAL "RelWithDebInfo")		
			install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/../bin/VkLayer_khronos_validation.dll" DESTINATION "${CMAKE_INSTALL_BINDIR}")
		endif()
	endif()
endif()

install(TARGETS yaml-cpp
	LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
	RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}")

if (SHARED_BUILD)
	install(TARGETS SDL2main SDL2
		LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
		RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}")
else()
	install(TARGETS SDL2main SDL2-static
		LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
		RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}")
endif()

if (COMPILER_SUPPORTS_CXX20)
	if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
		target_compile_options(${PROJECT_NAME} PRIVATE "-std=c++20")
	elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
		target_compile_options(${PROJECT_NAME} PRIVATE "/std:c++20")
	endif()
endif ()

if (COMPILER_SUPPORTS_WALL)
	if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
		target_compile_options(${PROJECT_NAME} PRIVATE "/Wall")
		target_compile_options(${PROJECT_NAME} PRIVATE $<$<CXX_COMPILER_ID:MSVC>:/W4>)
	elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
		target_compile_options(${PROJECT_NAME} PRIVATE "-Wall")
	endif()
endif ()

if (COMPILER_SUPPORTS_WEXTRA)
	if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
		target_compile_options(${PROJECT_NAME} PRIVATE "-Wextra")
	endif()
endif ()

# Macros
if (XORG_SUPPORT)
	target_compile_definitions(${PROJECT_NAME} PRIVATE PATATA_LINUX_XORG_SUPPORT=1)
endif()

if (${CMAKE_BUILD_TYPE} STREQUAL "Release")
	target_compile_definitions(${PROJECT_NAME} PRIVATE PATATA_BUILD_TYPE="Release")
elseif(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
	target_compile_definitions(${PROJECT_NAME} PRIVATE PATATA_BUILD_TYPE="Debug")
	target_compile_definitions(${PROJECT_NAME} PUBLIC DEBUG=1)
elseif(${CMAKE_BUILD_TYPE} STREQUAL "RelWithDebInfo")
	target_compile_definitions(${PROJECT_NAME} PRIVATE PATATA_BUILD_TYPE="Debug Optimized")
	target_compile_definitions(${PROJECT_NAME} PUBLIC DEBUG=1)
elseif(${CMAKE_BUILD_TYPE} STREQUAL "MinSizeRel")
	target_compile_definitions(${PROJECT_NAME} PRIVATE PATATA_BUILD_TYPE="Minimal Size Release")
endif()

if (NOT "${CMAKE_GENERATOR_VERSION}" STREQUAL "")
	target_compile_definitions(${PROJECT_NAME} PRIVATE PATATA_BUILD_SYSTEM_GENERATOR_VERSION="${CMAKE_GENERATOR_VERSION}")
endif()

target_compile_definitions(${PROJECT_NAME} PRIVATE
	PATATA_BUILD_SYSTEM="CMake"
	PATATA_BUILD_SYSTEM_VERSION="${CMAKE_VERSION}"
	PATATA_BUILD_SYSTEM_GENERATOR="${CMAKE_GENERATOR}"
	PATATA_ENGINE_VERSION="${PATATA_ENGINE_VERSION}"
	PATATA_ENGINE_VERSION_MAYOR=${PATATA_ENGINE_VERSION_MAYOR}
	PATATA_ENGINE_VERSION_MINOR=${PATATA_ENGINE_VERSION_MINOR}
	PATATA_ENGINE_VERSION_PATCH=${PATATA_ENGINE_VERSION_PATCH}
	PATATA_ENGINE_NAME="Patata Engine"
	PATATA_COMPILER_PROGRAM="${compiler_program}"
	PATATA_COMPILER_VERSION="${CMAKE_CXX_COMPILER_VERSION}"
	PATATA_ARCH="${CMAKE_SYSTEM_PROCESSOR}"
	PATATA_GIT_BRANCH="${PATATA_GIT_BRANCH}"
	PATATA_GIT_HASH_LONG="${PATATA_GIT_HASH_LONG}"
	PATATA_GIT_HASH_SHORT="${PATATA_GIT_HASH_SHORT}"
	PATATA_GIT_WORK_DIR_IS_CLEAN="${PATATA_GIT_WORK_DIR_IS_CLEAN}"
	PATATA_GIT_WORK_DIR_IS_STAGED="${PATATA_GIT_WORK_DIR_IS_STAGED}"
	PATATA_FAST_IO_GIT_COMMIT_HASH_SHORT="${Fast_io_COMMIT_SHORT_HASH}")

if (USE_EXTERNAL_LIBS)
	target_compile_definitions(${PROJECT_NAME} PRIVATE
	PATATA_VULKAN_LOADER_VERSION="${PATATA_VULKAN_LOADER_VERSION}"
	PATATA_YAML_CPP_VERSION="${PATATA_YAML-CPP_VERSION}")
endif()

if (${CMAKE_BUILD_TYPE} STREQUAL "Debug" OR ${CMAKE_BUILD_TYPE} STREQUAL "RelWithDebInfo" AND USE_EXTERNAL_LIBS)
	target_compile_definitions(${PROJECT_NAME} PRIVATE
		PATATA_VULKAN_VALIDATION_LAYERS_VERSION="${PATATA_VULKAN_VALIDATION_LAYERS_VERSION}"
		PATATA_IMGUI_VERSION="${Imgui_VERSION}")
endif()

if (DEFINED GAME_NAME)
	target_compile_definitions(${PROJECT_NAME} PUBLIC PATATA_GAME_NAME="${GAME_NAME}")
endif()

if (DEFINED GAME_VERSION_MAYOR AND DEFINED GAME_VERSION_MINOR AND GAME_VERSION_PATCH)
	target_compile_definitions(${PROJECT_NAME} PUBLIC
		PATATA_GAME_VERSION_MAYOR=${GAME_VERSION_MAYOR}
		PATATA_GAME_VERSION_MINOR=${GAME_VERSION_MINOR}
		PATATA_GAME_VERSION_PATCH=${GAME_VERSION_PATCH})
endif()

if (USE_EXTERNAL_LIBS)
	# Linux or MSVC
	if (MSVC OR LINUX OR CMAKE_SYSTEM_NAME STREQUAL "Linux")
		target_link_libraries(${PROJECT_NAME} PUBLIC vulkan)

		set_target_properties(asm_offset
			PROPERTIES
			ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
			LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
			RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
	endif()

	#Linux
	if (LINUX OR CMAKE_SYSTEM_NAME STREQUAL "Linux")
		if (${CMAKE_BUILD_TYPE} STREQUAL "Debug" OR ${CMAKE_BUILD_TYPE} STREQUAL "RelWithDebInfo")
			target_link_libraries(${PROJECT_NAME} PRIVATE
			VkLayer_khronos_validation
			-L${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

			file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/../tools/debug_run_patata_engine.sh"
				DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
		endif()
	endif()

	# MSYS2 Vulkan Link
	if (NOT MSVC AND (WIN32 OR CMAKE_SYSTEM_NAME STREQUAL "Windows"))
		target_link_libraries(${PROJECT_NAME} PUBLIC
			-lvulkan-1
			-L${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

		if (${CMAKE_BUILD_TYPE} STREQUAL "Debug" OR ${CMAKE_BUILD_TYPE} STREQUAL "RelWithDebInfo")
			target_link_libraries(${PROJECT_NAME} PUBLIC
				-lVkLayer_khronos_validation
				-L${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
		endif()
	endif()

	if (SHARED_BUILD)
		target_link_libraries(${PROJECT_NAME} PUBLIC SDL2main SDL2::SDL2)
	else()
		target_link_libraries(${PROJECT_NAME} PUBLIC SDL2main SDL2-static)

		if (NOT MSVC)
			if ((WIN32 OR CMAKE_SYSTEM_NAME STREQUAL "Windows") OR (LINUX OR CMAKE_SYSTEM_NAME STREQUAL "Linux"))
				target_link_libraries(${PROJECT_NAME} PRIVATE -static-libgcc -static-libstdc++)
			endif()
		endif()
	endif()
else()
	# Package Mananger
	target_link_libraries(${PROJECT_NAME} PUBLIC
		${Vulkan_LIBRARIES}
		${SDL2_LIBRARIES}
		Vulkan-Headers)
endif()

target_link_libraries(${PROJECT_NAME} PUBLIC Fast_io Glad2 yaml-cpp)

if (${CMAKE_BUILD_TYPE} STREQUAL "Debug" OR ${CMAKE_BUILD_TYPE} STREQUAL "RelWithDebInfo")
	target_link_libraries(${PROJECT_NAME} PUBLIC Imgui)
endif()

if (MSVC)
	set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "Engine")
	set_target_properties(Glad2 PROPERTIES FOLDER "Engine/Dependencies")

	if (USE_EXTERNAL_LIBS)
		#Yaml-cpp
		set_target_properties(yaml-cpp PROPERTIES FOLDER "Engine/Dependencies")
		set_target_properties(uninstall PROPERTIES FOLDER "Engine/Others/yamlcpp")
		# move CTest of yaml-cpp
		set_target_properties(Continuous PROPERTIES FOLDER "Engine/Others/yamlcpp")
		set_target_properties(Nightly PROPERTIES FOLDER "Engine/Others/yamlcpp")
		set_target_properties(Experimental PROPERTIES FOLDER "Engine/Others/yamlcpp")
		set_target_properties(NightlyMemoryCheck PROPERTIES FOLDER "Engine/Others/yamlcpp")

		#SDL2
		if (SHARED_BUILD)
			set_target_properties(SDL2 PROPERTIES FOLDER "Engine/Dependencies/SDL2")
		endif()
		set_target_properties(SDL2main PROPERTIES FOLDER "Engine/Dependencies/SDL2")
		if (TARGET SDL2-static)
			set_target_properties(SDL2-static PROPERTIES FOLDER "Engine/Dependencies/SDL2")
		endif()
		if (TARGET SDL2_test)
			set_target_properties(SDL2_test PROPERTIES FOLDER "Engine/Others/SDL2")
		endif()
		set_target_properties(sdl_headers_copy PROPERTIES FOLDER "Engine/Others/SDL2")

		#Vulkan
		set_target_properties(asm_offset PROPERTIES FOLDER "Engine/Others/Vulkan")
		set_target_properties(loader_specific_options PROPERTIES FOLDER "Engine/Others/Vulkan")
		set_target_properties(loader-unknown-chain PROPERTIES FOLDER "Engine/Others/Vulkan")
		set_target_properties(loader-opt PROPERTIES FOLDER "Engine/Others/Vulkan")
		set_target_properties(loader_asm_gen_files PROPERTIES FOLDER "Engine/Others/Vulkan")
		if (${CMAKE_BUILD_TYPE} STREQUAL "Debug" OR ${CMAKE_BUILD_TYPE} STREQUAL "RelWithDebInfo")
			set_target_properties(vvl PROPERTIES FOLDER "Engine/Dependencies/Vulkan")
			set_target_properties(VkLayer_utils PROPERTIES FOLDER "Engine/Dependencies/Vulkan")
			set_target_properties(vulkan PROPERTIES FOLDER "Engine/Dependencies/Vulkan")
		else()
			set_target_properties(vulkan PROPERTIES FOLDER "Engine/Dependencies")
		endif()
	endif()

	#Imgui
	if (${CMAKE_BUILD_TYPE} STREQUAL "Debug" OR ${CMAKE_BUILD_TYPE} STREQUAL "RelWithDebInfo")
		set_target_properties(Imgui PROPERTIES FOLDER "Engine/Dependencies")
	endif()
endif()

set_target_properties(${PROJECT_NAME}
	PROPERTIES
	VERSION "0")

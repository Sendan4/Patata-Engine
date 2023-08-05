include_directories("../include")

set(PATATA_SOURCE
	"Core/main.cpp"
	"Core/Start_And_End.cpp"
	"Core/Main_Loop.cpp"
	"Core/API_Graphics_Switch.cpp"
	"Window/Window.cpp"
	"Window/Window_Icon.cpp"
	"Vulkan/Setup_Vulkan.cpp"
	"Opengl/Opengl_Context.cpp"
	"Log/OpenGL_Info.cpp"
	"Log/Mapache.cpp"
	"Log/Start_Patata_Log_Info.cpp")

set(PATATA_ICON "Core/patata.rc")

add_executable(${PROJECT_NAME} ${PATATA_SOURCE})

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
	target_sources(${PROJECT_NAME} PRIVATE ${PATATA_ICON})
endif()

if (USE_EXTERNAL_LIBS)
	# Linux or MSVC
	if (MSVC OR LINUX OR CMAKE_SYSTEM_NAME STREQUAL "Linux")
		target_link_libraries(${PROJECT_NAME} PRIVATE vulkan)
	endif()

	# Linux
	if (LINUX OR CMAKE_SYSTEM_NAME STREQUAL "Linux")
		if (${CMAKE_BUILD_TYPE} STREQUAL "Debug" OR ${CMAKE_BUILD_TYPE} STREQUAL "RelWithDebInfo")
			target_link_libraries(${PROJECT_NAME} PRIVATE VkLayer_khronos_validation)
		endif()
	endif()

	# MSYS2 Vulkan Link
	if (NOT MSVC AND (WIN32 OR CMAKE_SYSTEM_NAME STREQUAL "Windows"))
		target_link_libraries(${PROJECT_NAME} PRIVATE
			-lvulkan-1
			-L${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

		if (${CMAKE_BUILD_TYPE} STREQUAL "Debug" OR ${CMAKE_BUILD_TYPE} STREQUAL "RelWithDebInfo") 
			target_link_libraries(${PROJECT_NAME} PRIVATE
				-lVkLayer_khronos_validation
				-L${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
		endif()
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

target_link_libraries(${PROJECT_NAME} PRIVATE Glad2)

include_directories(include/)

if (SHARED_BUILD)
	add_library(${PROJECT_NAME} SHARED)
else ()
	add_library(${PROJECT_NAME} STATIC)
endif ()

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
	"Opengl/Opengl_Context.cpp"
	"Opengl/OpenGL_Set_ViewPort_And_Resize.cpp"
	"Opengl/OpenGL_Renderer.cpp"
	"Log/Mapache.cpp")

if (ENABLE_ICON)
	target_sources (${PROJECT_NAME} PRIVATE
		"Window/Window_Icon.cpp")
endif()

if (CMAKE_SYSTEM_NAME STREQUAL "Windows" OR WIN32)
	target_sources (${PROJECT_NAME} PRIVATE
		"Log/Win/Start_Patata_Log_Info_Win.cpp"
		"Log/Win/Window_Icon_Set_Status_Win.cpp"
		"Log/Win/Setup_Vulkan_Log_Win.cpp"
		"Log/Win/Vulkan_Info_Win.cpp"
		"Log/Win/OpenGL_Info_Win.cpp")
else()
	target_sources (${PROJECT_NAME} PRIVATE
		"Log/Start_Patata_Log_Info.cpp"
		"Log/Window_Icon_Set_Status.cpp"
		"Log/Setup_Vulkan_Log.cpp"
		"Log/Vulkan_Info.cpp"
		"Log/OpenGL_Info.cpp")
endif()

target_include_directories(${PROJECT_NAME} PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}/include/"
	"${CMAKE_BINARY_DIR}/externals/SDL/include"
	"${CMAKE_CURRENT_SOURCE_DIR}/../externals/Vulkan-Headers/include")

message("")
message(STATUS "Vulkan-Headers Directory: ${CMAKE_CURRENT_SOURCE_DIR}/../externals/Vulkan-Headers/include")

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

			file(COPY "${CMAKE_SOURCE_DIR}/scripts/debug_run_patata_engine.sh"
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
		${SDL2_LIBRARIES})
endif()

target_link_libraries(${PROJECT_NAME} PUBLIC Glad2 yaml-cpp)

if (${CMAKE_BUILD_TYPE} STREQUAL "Debug" OR ${CMAKE_BUILD_TYPE} STREQUAL "RelWithDebInfo")
	target_link_libraries(${PROJECT_NAME} PUBLIC Imgui)
endif()

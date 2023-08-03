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

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
	add_executable(${PROJECT_NAME}
		${PATATA_SOURCE}
		${PATATA_ICON})
else()
	add_executable(${PROJECT_NAME}
		${PATATA_SOURCE})
endif()

if (SHARED_BUILD)
	# Attempt Shared
	if (USE_EXTERNAL_LIBS)
		if (MSVC)
			target_link_libraries(${PROJECT_NAME} PRIVATE
				vulkan
				Glad2
				SDL2main SDL2::SDL2)
		elseif(NOT MSVC AND WIN32)
			# Windows MSYS2
			target_link_libraries(${PROJECT_NAME} PRIVATE
				-lvulkan-1
				-L/${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/)

			target_link_libraries(${PROJECT_NAME} PRIVATE
				Glad2
				SDL2main SDL2::SDL2)
		elseif(NOT MSVC)
			#Linux
			target_link_libraries(${PROJECT_NAME} PRIVATE
				vulkan
				Glad2
				SDL2main SDL2::SDL2)
		endif()
	else()
		target_link_libraries(${PROJECT_NAME} PRIVATE
			Glad2
			${SDL2_LIBRARIES}
			${Vulkan_LIBRARIES})
	endif()
else()
	# Attempt Static
	if (USE_EXTERNAL_LIBS)
		if (MSVC)
			target_link_libraries(${PROJECT_NAME} PRIVATE
				vulkan
				Glad2
				SDL2main SDL2-static)
		elseif (NOT MSVC AND WIN32)
			# Windows MSYS2
			target_link_libraries(${PROJECT_NAME} PRIVATE
				-lvulkan-1
				-L/${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/)

			target_link_libraries(${PROJECT_NAME} PRIVATE
				Glad2
				SDL2main SDL2-static
				-static-libgcc
				-static-libstdc++)
		elseif(NOT MSVC)
			#Linux
			target_link_libraries(${PROJECT_NAME} PRIVATE
				vulkan
				Glad2
				SDL2main SDL2-static)
		endif()
	else()
		# Package Mananger
		target_link_libraries(${PROJECT_NAME} PRIVATE
			Glad2
			${SDL2_LIBRARIES}
			${Vulkan_LIBRARIES})
	endif()
endif()

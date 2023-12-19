#include <cstring>
#include <algorithm>
#if defined(__linux__)
#include <cstdlib>
#endif

#include <fast_io.h>
#include <yaml-cpp/yaml.h>

#if defined(DEBUG)
#include <imgui_impl_sdl2.h>
#include <imgui_impl_opengl3.h>
#endif

#if defined(_WIN64)
	#include <windows.h>

	extern "C" {
		__declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
		__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
	}
#endif

// Patata Engine
#include "PatataEngine/PatataEngine.hpp"
#include "Log.hpp"

#if defined(PATATA_GAME_NAME)
	#define GAME_CONFIG_FILE_NAME PATATA_GAME_NAME ".yaml"
#else
	#define GAME_CONFIG_FILE_NAME "patata.yaml"
#endif

Patata::Engine::Engine(void) {
	Patata::Log::StartMapache();
	Patata::Log::StartPatataLogInfo();
	
	try {
		#if defined(PATATA_GAME_NAME)
		Config = YAML::LoadFile(strcpy(SDL_GetBasePath(), GAME_CONFIG_FILE_NAME));
		#else
		Config = YAML::LoadFile(strcpy(SDL_GetBasePath(), "patata.yaml"));
		#endif
	}
	catch(const YAML::BadFile) {
		Patata::Log::YamlFileErrorMessage();
		exit(-1);
	}

	#if defined(__linux__)
	{
		/*
		if (strcmp(getenv("XDG_CURRENT_DESKTOP"), "GNOME") == 0)
			if (setenv("LIBDECOR_PLUGIN_DIR", SDL_GetBasePath(), 1) != 0)
				Patata::Log::ErrorMessage("Cannot set enviroment varible LIBDECOR_PLUGIN_DIR");*/

		/*
		if (setenv("VK_LAYER_PATH", SDL_GetBasePath(), 1) != 0)
			Patata::Log::ErrorMessage("Cannot set enviroment varible VK_LAYER_PATH");*/

		if (Config["patata-engine"]["prefer-wayland"].as<bool>())
			if(setenv("SDL_VIDEODRIVER", "wayland", 1) != 0)
				Patata::Log::ErrorMessage("Cannot set enviroment varible SDL_VIDEODRIVER");
	}
	#endif
	
	{
		std::string GraphicsAPI = Config["patata-engine"]["raccoon-renderer"]["graphics-api"].as<std::string>();
		std::transform(GraphicsAPI.begin(), GraphicsAPI.end(), GraphicsAPI.begin(), ::toupper);

		if (GraphicsAPI == "VULKAN")
			bGraphicsAPI = Patata::GraphicsAPI::Vulkan;
		else if (GraphicsAPI == "OPENGL")
			bGraphicsAPI = Patata::GraphicsAPI::OpenGL;
	}
}

#if defined(__GNUC__) || defined(__MINGW64__)
#include <cxxabi.h>
#endif
#if defined(_WIN64)
#else
#include "TerminalColors.hpp"
#endif
#include "ExitLog.hpp"

Patata::Engine::~Engine(void) {
	if (bGraphicsAPI) {
		// Vulkan
		Patata::Log::DeleteAndLogPtr("Vulkan Renderer", pVulkanRenderer);
	} 
	else {		
		// OpenGL
		Patata::Log::DeleteAndLogPtr("OpenGL Renderer", pOpenGLRenderer);
	}
}

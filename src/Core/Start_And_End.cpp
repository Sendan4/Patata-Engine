#include <cstring>
#include <algorithm>
#if defined(__linux__)
#include <cstdlib>
#endif

#include <fast_io.h>

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
	catch(const YAML::BadFile & BadFile) {
		Patata::Log::YamlFileErrorMessage();
		exit(1);
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

	#if defined(PATATA_FIND_VVL_IN_THE_CURRENT_PATH)
		#if defined(_WIN64)
			if(SetEnvironmentVariable("VK_LAYER_PATH", ".") == 0)
				Patata::Log::ErrorMessage("Cannot set enviroment varible VK_LAYER_PATH");
		#else
			if(setenv("VK_LAYER_PATH", ".", 1) != 0)
				Patata::Log::ErrorMessage("Cannot set enviroment varible VK_LAYER_PATH");
		#endif
	#endif
	
	{
		std::string GraphicsAPI = Config["patata-engine"]["raccoon-renderer"]["graphics-api"].as<std::string>();
		std::transform(GraphicsAPI.begin(), GraphicsAPI.end(), GraphicsAPI.begin(), ::toupper);

		if (GraphicsAPI == "VULKAN")
			bGraphicsAPI = Patata::GraphicsAPI::Vulkan;
		else if (GraphicsAPI == "OPENGL")
			bGraphicsAPI = Patata::GraphicsAPI::OpenGL;
	}

	try {
		if (SDL_Init(SDL_INIT_VIDEO) != 0) {
			Patata::Log::FatalErrorMessage("SDL2", "Cannot init the video subsystem", Config);
			throw Patata::RunTimeError("SDL Cannot init the video subsystem");
		}
	}
	catch (const Patata::RunTimeError & Error) { exit(1); }

	try {
		if (SDL_Init(SDL_INIT_EVENTS) != 0) {
			Patata::Log::FatalErrorMessage("SDL2", "Cannot init the events subsystem", Config);
			throw Patata::RunTimeError("SDL Cannot init the events subsystem");
		}
	}
	catch (const Patata::RunTimeError & Error) { exit(1); }

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
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
		SDL_GL_DeleteContext(Info->pOpenGLContext);
		delete Info->pOpenGLContext;
	}
}

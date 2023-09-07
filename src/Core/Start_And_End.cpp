#include <iostream>
#include <cstdint>
#include <cstring>
#include <algorithm>

#include <SDL.h>
#include <glad/gl.h>
#include <yaml-cpp/yaml.h>

#if defined(_WIN64)
	#include <windows.h>

	extern "C" {
		__declspec(dllexport) unsigned long NvOptimusEnablement = 0x00000001;
		__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
	}
#endif

// Patata Engine
#include "Patata_Engine/Patata_Engine.hpp"
#include "Patata_Engine/Window.hpp"
#include "Patata_Engine/Log.hpp"

Patata::PatataEngine::PatataEngine(
		std::string WINDOW_NAME,
		uint64_t WINDOW_INITIAL_WIDTH,
		uint64_t WINDOW_INITIAL_HEIGHT) {
	Patata::Log::StartMapache();
	Patata::Log::StartPatataLogInfo();

	config = YAML::LoadFile(strcpy(SDL_GetBasePath(), "patata.yaml"));

	// SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
		std::cout << "SDL - fail to start : " << SDL_GetError() << "\n";
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Problems starting", "SDL Failed to start subsystems", NULL);
	}
	
	{
		std::string GraphicsAPI = config["graphics-api"].as<std::string>();
		std::transform(GraphicsAPI.begin(), GraphicsAPI.end(), GraphicsAPI.begin(), ::toupper);

		if (GraphicsAPI == "VULKAN")
			bGraphicsAPI = true;
		else if (GraphicsAPI == "OPENGL")
			bGraphicsAPI = false;
	}

	// Create Window
	pWindow = new Patata::Window(
			WINDOW_NAME,
			WINDOW_INITIAL_WIDTH,
			WINDOW_INITIAL_HEIGHT,
			bGraphicsAPI);
	
	// SDL_Event
	MainEvent = new SDL_Event;
	
	if (bGraphicsAPI) {
		// Vulkan
		pVulkanRenderer = new Patata::Graphics::VulkanRenderer(pWindow->WindowGet(), config);
	}
	else {
		// OpenGL
		pOpenGLContext = new Patata::Graphics::OpenGLContext(pWindow->WindowGet(), config);
		pOpenGLRenderer = new Patata::Graphics::OpenGLRenderer();
		pOpenGLRenderer->OpenGLSetViewPort(WINDOW_INITIAL_WIDTH, WINDOW_INITIAL_HEIGHT);
		{
			if (config["vsync"].as<bool>())
				SDL_GL_SetSwapInterval(1);
			else
				SDL_GL_SetSwapInterval(0);
		}
	}
}

Patata::PatataEngine::~PatataEngine(void) {
	if (bGraphicsAPI) {
		// Vulkan
		delete pVulkanRenderer;
		pVulkanRenderer = nullptr;
	} 
	else {
		// OpenGL
		delete pOpenGLContext;
		pOpenGLContext = nullptr;
		delete pOpenGLRenderer;
		pOpenGLRenderer = nullptr;
	}

	// SDL_Event
	delete MainEvent;
	MainEvent = nullptr;
	
	// Window
	delete pWindow;
	pWindow = nullptr;

	// SDL
	SDL_Quit(); 
}

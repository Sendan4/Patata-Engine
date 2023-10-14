#include <iostream>
#include <cstdint>
#include <cstring>
#include <algorithm>

#include <SDL.h>
#include <glad/gl.h>
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
#include "PatataEngine/Window.hpp"
#include "PatataEngine/Log.hpp"

Patata::PatataEngine::PatataEngine(
		std::string WINDOW_NAME,
		uint64_t WINDOW_INITIAL_WIDTH,
		uint64_t WINDOW_INITIAL_HEIGHT) {
	Patata::Log::StartMapache();
	Patata::Log::StartPatataLogInfo();

	#if defined(GAME_NAME)
	config = YAML::LoadFile(strcpy(SDL_GetBasePath(), GAME_CONFIG_FILE_NAME));
	#else
	config = YAML::LoadFile(strcpy(SDL_GetBasePath(), "patata.yaml"));
	#endif

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
		
		#if defined(DEBUG)
		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO &io = ImGui::GetIO();
		io.ConfigFlags = ImGuiConfigFlags_NavEnableKeyboard | ImGuiConfigFlags_NavEnableGamepad;
		io.Fonts->AddFontDefault();
		io.IniFilename = NULL;
		io.LogFilename = NULL;
		ImGui::StyleColorsDark();
		#endif

		pOpenGLContext = new Patata::Graphics::OpenGLContext(pWindow->WindowGet(), config);
		pOpenGLRenderer = new Patata::Graphics::OpenGLRenderer();
		pOpenGLRenderer->OpenGLSetViewPort(WINDOW_INITIAL_WIDTH, WINDOW_INITIAL_HEIGHT);

		#if defined(DEBUG)
		ImGui_ImplOpenGL3_Init("#version 140");
		#endif

		if (config["vsync"].as<bool>())
			SDL_GL_SetSwapInterval(-1);
		else
			SDL_GL_SetSwapInterval(0);
	}
}

Patata::PatataEngine::~PatataEngine(void) {
	if (bGraphicsAPI) {
		// Vulkan
		delete pVulkanRenderer;
		pVulkanRenderer = nullptr;
	} 
	else {
		// Imgui
		#if defined(DEBUG)
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplSDL2_Shutdown();
		ImGui::DestroyContext();
		#endif

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

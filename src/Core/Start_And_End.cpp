#include <cstdint>
#include <cstring>
#include <algorithm>

#include <fast_io.h>
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
	
	try {
		#if defined(GAME_NAME)
		config = YAML::LoadFile(strcpy(SDL_GetBasePath(), GAME_CONFIG_FILE_NAME));
		#else
		config = YAML::LoadFile(strcpy(SDL_GetBasePath(), "patata.yaml"));
		#endif
	}
	catch(const YAML::BadFile) {
		Patata::Log::YamlFileErrorMessage();
		exit(-1);
	}

	// SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) > 0) {
		Patata::Log::FatalErrorMessage("SDL", SDL_GetError(), config);
		exit(-1);
	}
	
	{
		std::string GraphicsAPI = config["graphics-api"].as<std::string>();
		std::transform(GraphicsAPI.begin(), GraphicsAPI.end(), GraphicsAPI.begin(), ::toupper);

		if (GraphicsAPI == "VULKAN")
			bGraphicsAPI = true;
		else if (GraphicsAPI == "OPENGL")
			bGraphicsAPI = false;
	}
	
	// SDL_Event
	MainEvent = new SDL_Event;
	
	switch(bGraphicsAPI) {
		case true:
			// Vulkan
			try {
				// Create Window
				pWindow = new Patata::Window(
					WINDOW_NAME,
					WINDOW_INITIAL_WIDTH,
					WINDOW_INITIAL_HEIGHT,
					bGraphicsAPI,
					config);

				pVulkanRenderer = new Patata::Graphics::VulkanRenderer(pWindow->WindowGet(), config);

				break;
			}
			catch (...) {
				bGraphicsAPI = false;

				delete pVulkanRenderer;
				pVulkanRenderer = nullptr;

				delete pWindow;
				pWindow = nullptr;

				#if defined(_WIN64)
					fast_io::io::println(fast_io::out(), "Switching to OpenGL");
					fast_io::io::println(fast_io::out(), "Re-creating the window :");
				#else
					fast_io::io::println("Switching to OpenGL");
					fast_io::io::println("Re-creating the window :");
				#endif
			}

		case false:
			// Create Window
			pWindow = new Patata::Window(
				WINDOW_NAME,
				WINDOW_INITIAL_WIDTH,
				WINDOW_INITIAL_HEIGHT,
				bGraphicsAPI,
				config);

			// OpenGL
		
			#if defined(DEBUG)
			// Setup Dear ImGui context
			IMGUI_CHECKVERSION();
			ImGui::CreateContext();
			ImGuiIO &io = ImGui::GetIO();
			io.ConfigFlags = ImGuiConfigFlags_NavEnableKeyboard | ImGuiConfigFlags_NavEnableGamepad;

			static ImFontConfig cfg;
			cfg.OversampleH = cfg.OversampleV = 1;
			cfg.MergeMode = false;
			//cfg.FontBuilderFlags = ImGuiFreeTypeBuilderFlags_LoadColor;

			io.Fonts->AddFontDefault(&cfg);
			io.Fonts->Build();
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

			break;
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

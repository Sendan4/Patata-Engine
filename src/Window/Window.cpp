#include <cstdint>
#include <string>

#include <fast_io.h>
#include <SDL.h>

#include "PatataEngine/Window.hpp"
#include "PatataEngine/Log.hpp"

Patata::Window::Window(std::string WINDOW_NAME, uint64_t WINDOW_INITIAL_WIDTH, uint64_t WINDOW_INITIAL_HEIGHT, bool API_INITIAL, YAML::Node CONFIG) {
	if (WINDOW_NAME.empty())
		#if defined(GAME_NAME)
		WINDOW_NAME = GAME_NAME;
		#else
		WINDOW_NAME = "Patata Engine";
		#endif

	#if DEBUG
	WINDOW_NAME += " | Debug (Development)";
	#endif

	{
		uint32_t flags = 0;

		if (API_INITIAL)
			flags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_VULKAN;
		else flags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL; 

		WINDOW = SDL_CreateWindow(
			WINDOW_NAME.c_str(),
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			WINDOW_INITIAL_WIDTH,
			WINDOW_INITIAL_HEIGHT,
			flags);
	}

	if (!WINDOW) {
		Patata::Log::FatalErrorMessage("Window Error", SDL_GetError(), CONFIG);
		exit(-1);
	}
	#if defined (USE_ICON)
	else SetIcon(WINDOW, CONFIG);
	#endif
}

Patata::Window::~Window(void) {
	SDL_DestroyWindow(WINDOW);
	WINDOW = nullptr;
}

// Get
SDL_Window * Patata::Window::WindowGet(void) { return WINDOW; }

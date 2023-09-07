#include <iostream>
#include <cstdint>
#include <SDL.h>

#include "Patata_Engine/Window.hpp"

Patata::Window::Window(
		std::string WINDOW_NAME,
		uint32_t WINDOW_INITIAL_WIDTH,
		uint32_t WINDOW_INITIAL_HEIGHT,
		bool API_INITIAL) {
	if (WINDOW_NAME.empty())
		WINDOW_NAME = "Patata Engine";
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
		std::cout << "SDL - Window creation failed : " << SDL_GetError() << "\n";
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "SDL - Window creation failed", NULL);
	}
	else SetIcon(WINDOW);
}

Patata::Window::~Window(void) {
	SDL_DestroyWindow(WINDOW);
	WINDOW = nullptr;
}

// Get
SDL_Window * Patata::Window::WindowGet(void) { return WINDOW; }

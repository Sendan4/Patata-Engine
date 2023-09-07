#include <cstring>
#include <iostream>
#include <SDL.h>

#include "Patata_Engine/Window.hpp"
#include "Patata_Engine/Log.hpp"

void Patata::Window::SetIcon(SDL_Window * WINDOW) {
	SDL_Surface * WINDOW_ICON = SDL_LoadBMP(strcat(SDL_GetBasePath(), "patata.bmp"));

	if (WINDOW_ICON != nullptr)
		SDL_SetWindowIcon(WINDOW, WINDOW_ICON);

	SDL_FreeSurface(WINDOW_ICON);

	Patata::Log::WindowIconSetStatus(WINDOW_ICON);
}

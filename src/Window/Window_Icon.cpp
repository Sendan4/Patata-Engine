#include <cstring>
#include <iostream>
#include <SDL2/SDL.h>

#include "Core/Window.hpp"

void Patata::Window::SetIcon(SDL_Window * WINDOW) {
	SDL_Surface * WINDOW_ICON = SDL_LoadBMP(strcat(SDL_GetBasePath(), "patata.bmp"));
	if (WINDOW_ICON != nullptr) {
		SDL_SetWindowIcon(WINDOW, WINDOW_ICON);
		std::cout << "PATH : " << strcat(SDL_GetBasePath(), "patata.bmp") << " : " << SDL_GetError() << "\n";
	}
	SDL_FreeSurface(WINDOW_ICON);
}

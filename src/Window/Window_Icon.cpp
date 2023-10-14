#include <cstring>
#include <iostream>
#include <SDL.h>

#include "PatataEngine/Window.hpp"
#include "PatataEngine/Log.hpp"

#define GAME_ICON_FILE_NAME GAME_NAME ".bmp" 

void Patata::Window::SetIcon(SDL_Window * WINDOW) {
	#if defined(GAME_NAME)
	SDL_Surface * WINDOW_ICON = SDL_LoadBMP(strcat(SDL_GetBasePath(), GAME_ICON_FILE_NAME));
	#else
	SDL_Surface * WINDOW_ICON = SDL_LoadBMP(strcat(SDL_GetBasePath(), "patata.bmp"));
	#endif

	if (WINDOW_ICON != nullptr)
		SDL_SetWindowIcon(WINDOW, WINDOW_ICON);

	SDL_FreeSurface(WINDOW_ICON);

	Patata::Log::WindowIconSetStatus(WINDOW_ICON);
}

#pragma once
#include <SDL.h>
#include <iostream>

class Window {
    public:
		void start(void);
		void finish(void);
		
		//encapsulacion (get)
		SDL_Renderer * renderer_get(void);
 
    private:
		SDL_Window * WINDOW = nullptr;
		SDL_Surface * SURFACE = nullptr;
		SDL_Renderer * RENDER = nullptr;
};

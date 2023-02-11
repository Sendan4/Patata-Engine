#pragma once
#include <SDL.h>

class Window {
    public:
		void createWindowAndRender(void);
		void deleteWindowAndRender(void);
 
    private:
		SDL_Window * WINDOW;
		SDL_Renderer * RENDER;
};

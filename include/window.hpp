#pragma once
#include <SDL.h>
#include <iostream>

namespace Game {
	class Window {
    	public:
			void start(void);
			void finish(void);
		
			//encapsulacion (get)
			SDL_Renderer * renderer_get(void);
			SDL_Window * window_get(void);
			SDL_GLContext glcontext_get(void);
 
    	private:
			SDL_Window * WINDOW = nullptr;
			SDL_Renderer * RENDER = nullptr;
			SDL_GLContext OPENGL_CONTEXT = NULL;
	};
}
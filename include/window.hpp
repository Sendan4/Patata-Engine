#pragma once
#include <SDL.h>
#include <iostream>

namespace Game {
	class Window {
		public:
			void Start(const char *, int, int);
			void Finish(void);
		
			// Get
			SDL_Renderer * Renderer_get(void);
			SDL_Window * Window_get(void);
			SDL_GLContext glcontext_get(void);

		private:
			SDL_Window * Window = nullptr;
			SDL_Renderer * Render = nullptr;
			//SDL_GLContext OPENGL_CONTEXT = NULL;
	};
}

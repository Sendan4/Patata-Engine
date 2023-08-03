#pragma once

#include <SDL2/SDL.h>

namespace Patata {
	class Window {
		public:
			Window(std::string, uint32_t, uint32_t, bool);
			~Window();

			// Get
			SDL_Window * WindowGet(void);

			void SetIcon(SDL_Window *);

		private:
			SDL_Window * WINDOW;
	};
}


#pragma once

#include <cstdint>
#include <SDL.h>

namespace Patata {
	class Window {
		public:
			Window(std::string, uint32_t, uint32_t, bool);
			~Window();

			// Get
			SDL_Window * WindowGet(void);

			#if defined (USE_ICON)	
			void SetIcon(SDL_Window *);
			#endif

		private:
			SDL_Window * WINDOW;
	};
}

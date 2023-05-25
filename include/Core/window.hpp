#pragma once
#include <SDL.h>
#include <iostream>

enum GraphicsApi { VULKAN = true, OPENGL = false };

namespace Game {
	class Window {
		public:
			Window(std::string, int, int, bool);
			~Window();

			// Get
			SDL_Window * Window_get(void);

			// Set
			void Window_set(SDL_Window *);

			void SetIcon(SDL_Window *);

		private:
			SDL_Window * WINDOW;
	};
}

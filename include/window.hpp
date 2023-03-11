#pragma once
#include <SDL.h>
#include <iostream>
#include <vulkan/vulkan.hpp>

enum GraphicsApi { VULKAN = true, OPENGL = false };

namespace Game {
	class Window {
		public:
			Window(const char *, int, int, bool);
			bool WindowRendererStart(void);
			~Window();
		
			// Get
			SDL_Renderer * Renderer_get(void);
			SDL_Window * Window_get(void);

			// Set
			void Renderer_set(SDL_Renderer *);
			void Window_set(SDL_Window *);

			SDL_GLContext glcontext_get(void);

		private:
			SDL_Window * WINDOW = nullptr;
			SDL_Renderer * Render = nullptr;

			//SDL_GLContext OPENGL_CONTEXT = NULL;
	};
}

#include "window.hpp"
#include <vector>
#include <SDL_vulkan.h>

void Game::Window::Start(const char * Titulo, int Width, int Height) {
	Window = SDL_CreateWindow(
		Titulo,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		Width,
		Height,
		SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_VULKAN);

	// Vulkan
	// Obtener las extensiones
		unsigned int extensionInstanceCount = 0;
		if (!SDL_Vulkan_GetInstanceExtensions(Window, &extensionInstanceCount, nullptr))
			std::cout << "Error al obtener la lista de extensiones necesarias: " << SDL_GetError() << std::endl;

		std::vector<const char*> extensionInstanceNames(extensionInstanceCount);
		if (!SDL_Vulkan_GetInstanceExtensions(Window, &extensionInstanceCount, extensionInstanceNames.data()))
			std::cout << "Error al obtener la lista de extensiones necesarias: " << SDL_GetError() << std::endl;
		else {1
			std::cout << "| Vulkan Instance Extensions" << std::endl;
			for (int c = 0; c < int(extensionInstanceNames.size()); c++)
				std::cout << "|  · " << extensionInstanceNames[c] << std::endl;
			std::cout << std::endl;
		}

		if (!SDL_Vulkan_CreateSurface(Window, VulkanInstance, (VkSurfaceKHR*)&Surface))
			std::cout << " X No se pudo crear la Superficie" << std::endl;
	}

	SDL_Renderer * Render = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);

	if (!Window) {
		std::cout << "SDL - Fallo la creacion de la ventana : " << SDL_GetError() << std::endl;
		if (!Render) {
			std::cout << "SDL - El contexto de renderizado no es valido :" << SDL_GetError() << std::endl;
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "SDL - Fallo la creacion de la ventana\nSDL - El contexto de renderizado no es valido", NULL);
		}
		else
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "SDL - Fallo la creacion de la ventana", NULL);
	}

	SDL_RenderClear(Render);
	SDL_RenderPresent(Render);
}

void Game::Window::Finish(void) {
	SDL_DestroyRenderer(Render);
	SDL_DestroyWindow(Window);
}

// Get
SDL_Renderer * Game::Window::Renderer_get(void) { return Render; }
SDL_Window * Game::Window::Window_get(void) { return Window; }
//SDL_GLContext Game::Window::glcontext_get(void) { return OPENGL_CONTEXT; }

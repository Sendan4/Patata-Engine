#include <iostream>
#include <SDL.h>

// Patata Engine
#include "Core/Patata_Engine.hpp"
#include "Core/Window.hpp"
#include "Core/Log.hpp"
#include "Graphics/Vulkan.hpp"
//#include "Graphics/OpenGL.hpp"

Patata::Graphics::VulkanRenderer * pVulkanRenderer = nullptr;
//Patata::Graphics::OpenGLContext * pOpenGLContext = nullptr;
Patata::Window * pWindow = nullptr;

Patata::PatataEngine::PatataEngine(
		std::string WINDOW_NAME,
		uint32_t WINDOW_INITIAL_WIDTH,
		uint32_t WINDOW_INITIAL_HEIGHT,
		bool API_INITIAL) {
	Patata::Log::StartMapache();
	Patata::Log::StartPatataLogInfo();

	// SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
		std::cout << "SDL - Video SubSystem failed to start : " << SDL_GetError() << "\n";
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Problems starting", "SDL Failed to start subsystems", NULL);
	}

	// Create Window
	pWindow = new Patata::Window(WINDOW_NAME, WINDOW_INITIAL_WIDTH, WINDOW_INITIAL_HEIGHT, API_INITIAL);

	// OpenGL
	//pOpenGLContext = new Patata::Graphics::OpenGLContext(pWindow->WindowGet());
	
	// Vulkan
	pVulkanRenderer = new Patata::Graphics::VulkanRenderer(pWindow->WindowGet());
}

void Patata::PatataEngine::GLSwapMainLoopWrapper(void) {
	SDL_GL_SwapWindow(pWindow->WindowGet());
};

Patata::PatataEngine::~PatataEngine(void) {
	// Vulkan
	delete pVulkanRenderer;
	pVulkanRenderer = nullptr;

	// OpenGL
	//delete pOpenGLContext;
	//pOpenGLContext = nullptr;
	
	// Window
	delete pWindow;
	pWindow = nullptr;

	// SDL
	SDL_Quit(); 
}

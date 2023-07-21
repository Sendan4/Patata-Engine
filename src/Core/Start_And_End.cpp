#include <iostream>
#include <SDL.h>

// Patata Engine
#include "Core/Patata_Engine.hpp"
#include "Core/Window.hpp"
#include "Core/Log.hpp"
#include "Graphics/OpenGL.hpp"

Patata::Graphics::OpenGLContext * pOpenGLContext = nullptr;
Patata::Window * pWindow = nullptr;

Patata::PatataEngine::PatataEngine(
		std::string WINDOW_NAME = "Patata Engine",
		uint32_t WINDOW_INITIAL_WIDTH = 1280,
		uint32_t WINDOW_INITIAL_HEIGHT = 720,
		bool API_INITIAL = true) {
	Patata::Log::StartMapache();
	Patata::Log::StartPatataLogInfo();

	// SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
		std::cout << "SDL - SubSistema de video no se ha podido iniciar :" << SDL_GetError() << "\n";
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Problemas al iniciar", "SDL Fallo al iniciar los subsistemas", NULL);
	}

	// Create Window
	pWindow = new Patata::Window(WINDOW_NAME, WINDOW_INITIAL_WIDTH, WINDOW_INITIAL_HEIGHT, API_INITIAL);

	// OpenGL
	pOpenGLContext = new Patata::Graphics::OpenGLContext(pWindow->WindowGet());
}

void Patata::PatataEngine::GLSwapMainLoopWrapper(void) {
	SDL_GL_SwapWindow(pWindow->WindowGet());
};

Patata::PatataEngine::~PatataEngine(void) {
	// Window
	delete pWindow;
	pWindow = nullptr;

	// OpenGL
	delete pOpenGLContext;
	pOpenGLContext = nullptr;

	// SDL
	SDL_Quit(); 
}

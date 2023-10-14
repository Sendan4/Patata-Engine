#include <glad/gl.h>
#include <SDL.h>
#include <cstdint>

// Patata Engine 
#include "PatataEngine/Graphics/OpenGLRenderer.hpp"

void Patata::Graphics::OpenGLRenderer::OpenGLSetViewPort(uint64_t WINDOW_INITIAL_WIDTH, uint64_t WINDOW_INITIAL_HEIGHT) {
	glViewport(0, 0, WINDOW_INITIAL_WIDTH, WINDOW_INITIAL_HEIGHT);
}

void Patata::Graphics::OpenGLRenderer::OpenGLResizeViewPort(SDL_Window * WINDOW) {
	int width = 0, height = 0;
	SDL_GetWindowSize(WINDOW, &width, &height);

	glViewport(0, 0, width, height);
}

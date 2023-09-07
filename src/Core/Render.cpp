#include <glad/gl.h>
#include <SDL.h>

// Patata Engine
#include "Patata_Engine/Patata_Engine.hpp"
#include "Patata_Engine/Window.hpp"

void Patata::PatataEngine::Render(void) {
	if (bGraphicsAPI) {
		// Vulkan
	}
	else {
		// OpenGL
		if (MainEvent->type == SDL_WINDOWEVENT_SIZE_CHANGED)
			pOpenGLRenderer->OpenGLResizeViewPort(pWindow->WindowGet());

		glClearColor(0.113f, 0.578f, 0.810f, 0.5f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		SDL_GL_SwapWindow(pWindow->WindowGet());
	}
}

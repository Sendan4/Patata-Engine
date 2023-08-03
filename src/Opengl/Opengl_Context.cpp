#include <iostream>
#include <SDL2/SDL.h>
#include <glad/gl.h>

// Patata Engine
#include "Graphics/OpenGL.hpp"
#include "Core/Log.hpp"

Patata::Graphics::OpenGLContext::OpenGLContext(SDL_Window * WINDOW) {
	SetAttributes();
	CreateContext(WINDOW);
	Patata::Log::OpenGLInfo();
}

Patata::Graphics::OpenGLContext::~OpenGLContext(void) {
	SDL_GL_DeleteContext(GLCONTEXT);
	GLCONTEXT = NULL;
}

void Patata::Graphics::OpenGLContext::SetAttributes(void) {
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
}

void Patata::Graphics::OpenGLContext::CreateContext(SDL_Window * WINDOW) {
	GLCONTEXT = SDL_GL_CreateContext(WINDOW);
	if (!GLCONTEXT)
		std::cout << "Could not create OpenGL context" << std::endl;

	gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress);
}

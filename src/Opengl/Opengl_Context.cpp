#include <iostream>

#include <yaml-cpp/yaml.h>
#include <glad/gl.h>
#include <SDL.h>
#include <SDL_opengl.h>

#if defined(DEBUG)
#include <backends/imgui_impl_sdl2.h>
#endif

// Patata Engine
#include "Patata_Engine/Graphics/OpenGL_Context.hpp"
#include "Patata_Engine/Log.hpp"

Patata::Graphics::OpenGLContext::OpenGLContext(SDL_Window * WINDOW, YAML::Node CONFIG) {
	SetAttributes();
	CreateContext(WINDOW);
	Patata::Log::OpenGLInfo(CONFIG);
}

Patata::Graphics::OpenGLContext::~OpenGLContext(void) {
	SDL_GL_DeleteContext(SDLGLCONTEXT);
	SDLGLCONTEXT = NULL;
}

void Patata::Graphics::OpenGLContext::SetAttributes(void) {
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
}

void Patata::Graphics::OpenGLContext::CreateContext(SDL_Window * WINDOW) {
	SDLGLCONTEXT = SDL_GL_CreateContext(WINDOW);

	if (!SDLGLCONTEXT) {
		std::cout << "Could not create OpenGL context" << std::endl;
		return;
	}
	
	gladLoadGL(reinterpret_cast<GLADloadfunc>(SDL_GL_GetProcAddress));

	#if defined(DEBUG)
	ImGui_ImplSDL2_InitForOpenGL(WINDOW, SDLGLCONTEXT);
	#endif
}

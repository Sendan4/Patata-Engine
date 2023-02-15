#include <SDL.h>
#include <glad/glad.h>
#include <iostream>

void sdl_opengl_atributos(void) {
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
}

void start_opengl(SDL_Window * WINDOW,SDL_GLContext GL_CONTEXT) {
	GL_CONTEXT = SDL_GL_CreateContext(WINDOW);

	if (!gladLoadGLLoader(SDL_GL_GetProcAddress))
        std::cout << "No se pudo iniciar el contexto de OpenGL" << std::endl;
}
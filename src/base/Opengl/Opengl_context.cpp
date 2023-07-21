#include <glad/glad.h>
#include <SDL.h>
#include <iostream>
#include "terminal_colors.hpp"

namespace Graphics {
	void sdl_opengl_atributos(void) {
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	}

	SDL_GLContext start_opengl(SDL_Window * WINDOW) {
		SDL_GLContext context = SDL_GL_CreateContext(WINDOW);

		if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
			std::cout << "No se pudo iniciar el contexto de OpenGL" << std::endl;
			return NULL;
		}
		else {
			std::cout << FSteelBlue1 << Bold << "+ Informacion General de OpenGL :" << Reset << std::endl;
			std::cout << FSteelBlue1 << Bold << "| · Hardware Vendor: \t" << Reset << glGetString(GL_VENDOR) << Reset << std::endl;
			std::cout << FSteelBlue1 << Bold << "| · GPU / iGPU: \t" << Reset << glGetString(GL_RENDERER) << Reset << std::endl;
			std::cout << FSteelBlue1 << Bold << "| · OpenGL Version: \t" << Reset << glGetString(GL_VERSION) << Reset << std::endl;
			std::cout << FSteelBlue1 << Bold << "- · Shading Language Version: \t" << Reset << glGetString(GL_SHADING_LANGUAGE_VERSION) << Reset << std::endl;
		}
		return context;
	}
}

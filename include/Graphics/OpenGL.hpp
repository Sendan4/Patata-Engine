#pragma once

#include <SDL.h>

namespace Patata {
	namespace Graphics {
		class OpenGLContext {
			public:	
				OpenGLContext(SDL_Window *);
				~OpenGLContext(void);

			private:
				void SetAttributes(void);
				void CreateContext(SDL_Window *);

				SDL_GLContext GLCONTEXT = NULL;
		};
	}
}

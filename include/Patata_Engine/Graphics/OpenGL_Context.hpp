#pragma once

#include <cstdint>

#include <yaml-cpp/yaml.h>
#include <SDL.h>

namespace Patata {
	namespace Graphics {
		class OpenGLContext {
			public:	
				OpenGLContext(SDL_Window *, YAML::Node);
				~OpenGLContext(void);

			private:
				void SetAttributes(void);
				void CreateContext(SDL_Window *);

				SDL_GLContext SDLGLCONTEXT = NULL;
		};
	}
}

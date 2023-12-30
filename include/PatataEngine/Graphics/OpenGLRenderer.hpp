#include <SDL.h>

namespace Patata {
	namespace Graphics {
		class OpenGLRenderer {
			public:	
				OpenGLRenderer(YAML::Node & Config);
				~OpenGLRenderer(void);

				void OpenGLResizeViewPort(SDL_Window *);
				void OpenGLSetViewPort(uint32_t, uint32_t);
			private:
		};
	}
}

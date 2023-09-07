#include <cstdint>
#include <SDL.h>

namespace Patata {
	namespace Graphics {
		class OpenGLRenderer {
			public:	
				OpenGLRenderer(void);
				~OpenGLRenderer(void);

				void OpenGLResizeViewPort(SDL_Window *);
				void OpenGLSetViewPort(uint64_t, uint64_t);
			private:
		};
	}
}

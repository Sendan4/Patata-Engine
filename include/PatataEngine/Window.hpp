#pragma once

#include <cstdint>

#include <yaml-cpp/yaml.h>
#include <SDL.h>

namespace Patata {
	class Window {
		public:
			Window(std::string, uint64_t, uint64_t, bool, YAML::Node);
			~Window();

			// Get
			SDL_Window * WindowGet(void);

			#if defined (USE_ICON)	
			void SetIcon(SDL_Window *, YAML::Node);
			#endif

		private:
			SDL_Window * WINDOW;
	};
}

#pragma once

#if defined(_WIN64)
	#ifdef SHARED_LIBRARY_EXPORT_DEFINE
		#define PATATA_API __declspec(dllexport)
	#else
		#define PATATA_API
	#endif
#elif defined(__linux__)
	#define PATATA_API __attribute__((visibility("default")))
#endif

#include "PatataEngine/Graphics/RaccoonRenderer.hpp"

namespace Patata {
	class Engine {
		public:
			YAML::Node Config;

			PATATA_API Engine(const std::string &, const uint32_t &, const uint32_t &);
			PATATA_API ~Engine(void);
			
			PATATA_API void HandleEvent(SDL_Event &);
			PATATA_API void Render(void);

		private:
			SDL_Event * MainEvent = nullptr;
			SDL_Window * GameWindow = nullptr;
			Patata::Graphics::RaccoonRenderer * RaccoonRenderer = nullptr;

			void CreateGameWindow(const std::string &, const uint32_t &, const uint32_t &, const bool &);
			#if defined(USE_ICON)
				void SetWindowIcon(void);
			#endif

			#if defined(DEBUG)
				void SetupImGUIBackend(void);
				void ImGuiStartFrame(void);
				void DrawDebugUI(void);
				void ImGuiEndFrame(void);
			#endif
	};

	namespace Graphics {
		enum Backend : bool { Vulkan = true, OpenGL = false };
	}

	class RunTimeError : public std::exception {
    	private:
			std::string message;

    	public:
	    	RunTimeError(const std::string & msg) : message(msg) {}
			std::string what (void) {
    	    	return message;
    		}
	};
}

#pragma once

#if defined(_WIN64)
	#ifdef SHARED_LIBRARY_EXPORT_DEFINE
		#define PATATA_API __declspec(dllexport)
	#else
		#define PATATA_API __declspec(dllimport)
	#endif
#elif defined(__linux__)
	#define PATATA_API __attribute__((visibility("default")))
#endif

#if defined(PATATA_GAME_NAME)
	#define PATATA_GAME_ICON_FILE PATATA_GAME_NAME ".bmp"
#else
	#if defined(DEBUG)
		#define PATATA_GAME_ICON_FILE "patata-debug.bmp"
	#else
		#define PATATA_GAME_ICON_FILE "patata-release.bmp"
	#endif
#endif

#include "PatataEngine/Graphics/VulkanRenderer.hpp"
#include "PatataEngine/Graphics/OpenGLRenderer.hpp"

namespace Patata {

	struct EngineInfo{
		SDL_Window * pWindow = nullptr;
		SDL_GLContext * pOpenGLContext = nullptr;
	};

	class Engine {
		public:
			YAML::Node Config;
			const bool * pGraphicsAPI = &bGraphicsAPI;
			EngineInfo * Info = new EngineInfo;

			PATATA_API Engine (void);
			PATATA_API ~Engine (void);
			
			PATATA_API uint64_t GetWindowFlags(void);
			PATATA_API void HandleEvent(SDL_Event &);
			PATATA_API void InitRenderer(void);
			PATATA_API void Render(void);

			Patata::Graphics::VulkanRenderer * pVulkanRenderer = nullptr;
			Patata::Graphics::OpenGLRenderer * pOpenGLRenderer = nullptr;

		private:
			SDL_Event * MainEvent = nullptr;
			bool bGraphicsAPI;

			#if defined(DEBUG)
				void SetupImGUIBackend(void);
				void ImGuiStartFrame(void);
				void DrawDebugUI(void);
				void ImGuiEndFrame(void);
			#endif
	};

	enum GraphicsAPI : bool { Vulkan = true, OpenGL = false };

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

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

#include "PatataEngine/Graphics/VulkanRenderer.hpp"
#include "PatataEngine/Graphics/OpenGLRenderer.hpp"

namespace Patata {

	class Engine {
		public:
			YAML::Node Config;
			const bool * pGraphicsAPI = &bGraphicsAPI;

			PATATA_API Engine(const std::string &, const uint32_t &, const uint32_t &);
			PATATA_API ~Engine(void);
			
			PATATA_API void HandleEvent(SDL_Event &);
			PATATA_API void Render(void);

			Patata::Graphics::VulkanRenderer * pVulkanRenderer = nullptr;
			Patata::Graphics::OpenGLRenderer * pOpenGLRenderer = nullptr;

		private:
			SDL_Event * MainEvent = nullptr;
			SDL_Window * GameWindow = nullptr;
			SDL_GLContext * GameGLContext = nullptr;
			bool bGraphicsAPI;

			void CreateGameWindow(const std::string &, const uint32_t &, const uint32_t &);
			void SetWindowIcon(void);
			void InitRenderer(void);

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

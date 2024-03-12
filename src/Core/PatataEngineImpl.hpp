#pragma once

#ifndef YAML_CPP_API
#define YAML_CPP_API
#endif
#include <yaml-cpp/yaml.h>
#include <SDL.h>

#include "RaccoonRenderer.hpp"
#include "PatataEngine/PatataEngine.hpp"

namespace Patata {
	class Engine::EngineImpl {
		public:
			YAML::Node Config;

			EngineImpl(const std::string &, const uint32_t &, const uint32_t &);
			~EngineImpl(void);
	
			void HandleEvent(SDL_Event &);
			void Render(void);

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

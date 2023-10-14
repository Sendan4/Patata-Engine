#pragma once

#if defined(_WIN64)
	#ifdef SHARED_LIBRARY_EXPORT_DEFINE
		#define PATATA_SHARED __declspec(dllexport)
	#else
		#define PATATA_SHARED __declspec(dllimport)
	#endif
#elif defined(__linux__)
	#define PATATA_SHARED __attribute__((visibility("default")))
#endif

#if defined(GAME_NAME)
#define GAME_CONFIG_FILE_NAME GAME_NAME ".yaml"
#endif

#include <cstdint>
#include <string>

#include <SDL.h>
#include <yaml-cpp/yaml.h>

#include "PatataEngine/Window.hpp"
#include "PatataEngine/Graphics/VulkanRenderer.hpp"
#include "PatataEngine/Graphics/OpenGLContext.hpp"
#include "PatataEngine/Graphics/OpenGLRenderer.hpp"

namespace Patata {
	class PatataEngine {
		public:
			PATATA_SHARED PatataEngine (std::string, uint64_t, uint64_t);
			PATATA_SHARED ~PatataEngine (void);

			PATATA_SHARED bool Input(void);
			PATATA_SHARED void Render(void);
	
			Patata::Window * pWindow = nullptr;
			Patata::Graphics::VulkanRenderer * pVulkanRenderer = nullptr;
			Patata::Graphics::OpenGLContext * pOpenGLContext = nullptr;
			Patata::Graphics::OpenGLRenderer * pOpenGLRenderer = nullptr;

		private:
			YAML::Node config;
			SDL_Event * MainEvent = nullptr;
			bool bGraphicsAPI;
	};
}

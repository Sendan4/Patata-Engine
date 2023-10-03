#pragma once

// "undefined reference to" on windows
#if defined(_WIN64)
	#ifdef SHARED_LIBRARY_EXPORT_DEFINE
		#define SHARED_LIBRARY_EXPORT __declspec(dllexport)
	#else
		#define SHARED_LIBRARY_EXPORT __declspec(dllimport)
	#endif
#else
	#define SHARED_LIBRARY_EXPORT
#endif

#if defined(GAME_NAME)
#define GAME_CONFIG_FILE_NAME GAME_NAME ".yaml"
#endif

#include <cstdint>
#include <string>

#include <SDL.h>
#include <yaml-cpp/yaml.h>

#include "Window.hpp"
#include "Graphics/Vulkan_Renderer.hpp"
#include "Graphics/OpenGL_Context.hpp"
#include "Graphics/OpenGL_Renderer.hpp"

namespace Patata {
	class PatataEngine {
		public:
			SHARED_LIBRARY_EXPORT PatataEngine (std::string, uint64_t, uint64_t);
			SHARED_LIBRARY_EXPORT ~PatataEngine (void);

			SHARED_LIBRARY_EXPORT bool Input(void);
			SHARED_LIBRARY_EXPORT void Render(void);
	
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

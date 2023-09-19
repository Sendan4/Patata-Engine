#pragma once
#include <cstdint>
#include <string>

#include <SDL.h>
#include <yaml-cpp/yaml.h>

#include "Patata_Engine/Window.hpp"
#include "Patata_Engine/Graphics/Vulkan_Renderer.hpp"
#include "Patata_Engine/Graphics/OpenGL_Context.hpp"
#include "Patata_Engine/Graphics/OpenGL_Renderer.hpp"

namespace Patata {
	class PatataEngine {
		public:
			PatataEngine (std::string, uint64_t, uint64_t);
			~PatataEngine (void);

			void MainLoop(void);
			bool MainInput(void);
			void Render(void);
	
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

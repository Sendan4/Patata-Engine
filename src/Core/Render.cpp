#ifndef YAML_CPP_API
#define YAML_CPP_API
#endif
#include <yaml-cpp/yaml.h>
#include <SDL.h>
#include <vulkan/vulkan.hpp>
#include <glad/gl.h>

// Patata Engine
#include "PatataEngine/PatataEngine.hpp"

#if defined(DEBUG)
#include <imgui_impl_sdl2.h>
#include <imgui_impl_opengl3.h>
#endif

void Patata::Engine::Render(void) {
	if (*RaccoonRenderer->Backend == Patata::Graphics::Backend::Vulkan) {
	}
	else {
		// OpenGL
		#if defined(DEBUG)
		ImGuiStartFrame();
		DrawDebugUI();
		#else
		glClearColor(0.113f, 0.578f, 0.810f, 0.5f);
		#endif

		glClear(GL_COLOR_BUFFER_BIT);

		#if defined(DEBUG)	
		ImGuiEndFrame();
		#endif

		SDL_GL_SwapWindow(GameWindow);
	}
}

#include <imgui_impl_sdl2.h>
#include <imgui_impl_opengl3.h>

#ifndef YAML_CPP_API
#define YAML_CPP_API
#endif
#include <yaml-cpp/yaml.h>
#include <vulkan/vulkan.hpp>
#include <SDL.h>
#include "PatataEngine/PatataEngine.hpp"

void Patata::Engine::ImGuiStartFrame(void) {
	if (*RaccoonRenderer->Backend == Patata::Graphics::Backend::Vulkan) {
	}
	else {
		// OpenGL
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();
	}
}

void Patata::Engine::ImGuiEndFrame(void) {
	if (*RaccoonRenderer->Backend == Patata::Graphics::Backend::Vulkan) {
	}
	else {
		// OpenGL
	    ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
}

#include "ImGUIFrame.hpp"

void Patata::Engine::EngineImpl::ImGuiStartFrame(void) {
	if (*RaccoonRenderer->Backend == Patata::Graphics::Backend::Vulkan) {
	}
	else {
		// OpenGL
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();
	}
}

void Patata::Engine::EngineImpl::ImGuiEndFrame(void) {
	if (*RaccoonRenderer->Backend == Patata::Graphics::Backend::Vulkan) {
	}
	else {
		// OpenGL
	    ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
}

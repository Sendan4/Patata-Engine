#include <imgui_impl_sdl2.h>
#include <imgui_impl_opengl3.h>

#include "PatataEngine/PatataEngine.hpp"

void Patata::Engine::ImGuiStartFrame(void) {
	switch(bGraphicsAPI) {
		case Patata::GraphicsAPI::Vulkan:
			break;
	
		case Patata::GraphicsAPI::OpenGL:
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplSDL2_NewFrame();
			ImGui::NewFrame();
			break;
	}
}

void Patata::Engine::ImGuiEndFrame(void) {
	switch(bGraphicsAPI) {
		case Patata::GraphicsAPI::Vulkan:
			break;
	
		case Patata::GraphicsAPI::OpenGL:
	        ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
			break;
	}
}

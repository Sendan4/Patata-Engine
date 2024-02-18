#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_opengl3.h>
#include <yaml-cpp/yaml.h>
#include <vulkan/vulkan.hpp>
#include <SDL.h>

#include "PatataEngine/PatataEngine.hpp"

void Patata::Engine::SetupImGUIBackend(void) {
	if (*RaccoonRenderer->Backend == Patata::Graphics::Backend::Vulkan) {
	}
	else {
		// OpenGL
		IMGUI_CHECKVERSION();
    	ImGui::CreateContext();
    	ImGuiIO& io = ImGui::GetIO(); (void)io;
   		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.IniSavingRate = 0;
		io.IniFilename = nullptr;
		io.LogFilename = nullptr;

    	ImGui::StyleColorsDark();
		ImGuiStyle * style = &ImGui::GetStyle();
		style->FrameBorderSize = 0;

		ImGui_ImplSDL2_InitForOpenGL(GameWindow, RaccoonRenderer->GameGLContext);
		ImGui_ImplOpenGL3_Init("#version 130");
	}
}

#include <imgui_impl_sdl2.h>
#include <imgui_impl_opengl3.h>

#include "PatataEngine/PatataEngine.hpp"


void Patata::Engine::SetupImGUIBackend(void) {
	switch(bGraphicsAPI) {
		case Patata::GraphicsAPI::Vulkan:
			break;

		case Patata::GraphicsAPI::OpenGL:
			IMGUI_CHECKVERSION();
    		ImGui::CreateContext();
    		ImGuiIO& io = ImGui::GetIO(); (void)io;
   			io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
			io.IniSavingRate = 0;
			io.IniFilename = nullptr;
			io.LogFilename = nullptr;

    		ImGui::StyleColorsDark();
			ImGuiStyle * style = &ImGui::GetStyle();
			style->FrameBorderSize = 0;

			ImGui_ImplSDL2_InitForOpenGL(Info->pWindow, Info->pOpenGLContext);
			ImGui_ImplOpenGL3_Init("#version 130");
			break;
	}
}

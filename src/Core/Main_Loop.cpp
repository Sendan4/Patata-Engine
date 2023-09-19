#include <SDL.h>

#if defined(DEBUG)
#include <imgui.h>
#include <backends/imgui_impl_sdl2.h>
#include <backends/imgui_impl_opengl3.h>
#endif

// Patata Engine
#include "Patata_Engine/Patata_Engine.hpp"
#include "Patata_Engine/Window.hpp"

void Patata::PatataEngine::MainLoop(void) {
	do {
		if (!MainInput()) break;

		#if defined(DEBUG)
		if (bGraphicsAPI) {
			// Vulkan
		}
		else {
			// OpenGL
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplSDL2_NewFrame();
			ImGui::NewFrame();
		}
		#endif

		Render();
	} while (true);
}

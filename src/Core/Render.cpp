#include <glad/gl.h>
#include <SDL.h>

#if defined(DEBUG)
#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_opengl3.h>
#endif

// Patata Engine
#include "Patata_Engine.hpp"
#include "Window.hpp"

void Patata::PatataEngine::Render(void) {
	if (bGraphicsAPI) {
		// Vulkan
	}
	else {
		// OpenGL
		if (MainEvent->type == SDL_WINDOWEVENT_SIZE_CHANGED)
			pOpenGLRenderer->OpenGLResizeViewPort(pWindow->WindowGet());

		#if defined(DEBUG)
		{
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplSDL2_NewFrame();
			ImGui::NewFrame();

			ImGui::SetNextWindowSize(ImVec2(280, 200));
			ImGui::Begin("Patata Engine - Developer Tools", nullptr, ImGuiWindowFlags_NoResize);
			ImGui::Text("Tools coming soon");
			ImGui::End();
		}
		#endif

		#if defined(DEBUG)
		ImGui::Render();
		#endif

		glClearColor(0.113f, 0.578f, 0.810f, 0.5f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		#if defined(DEBUG)
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		#endif

		SDL_GL_SwapWindow(pWindow->WindowGet());
	}
}

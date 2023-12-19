#include <imgui.h>
#include <glad/gl.h>

#include "PatataEngine/PatataEngine.hpp"

void Patata::Engine::DrawDebugUI(void) {
	static ImVec4 color = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
	static bool firstpass = true;

	if (firstpass) {
		firstpass = false;
		switch(bGraphicsAPI) {
			case Patata::GraphicsAPI::OpenGL:
				color = ImVec4(0.113f, 0.578f, 0.810f, 1.0f);
				break;

			case Patata::GraphicsAPI::Vulkan:
				break;
		}
	}

	ImGui::SetNextWindowSize(ImVec2(500, 300));
	ImGui::Begin("Patata Engine | (Debug) Development", nullptr, ImGuiWindowFlags_NoResize);
	ImGui::BeginTabBar("Tools"); {
		ImGui::BeginTabItem("Tools"); {
			ImGui::ColorEdit3("Buffer Color", reinterpret_cast<float *>(&color));
			ImGui::Separator();
			ImGui::EndTabItem();
		}
		ImGui::EndTabBar();
	}
	ImGui::End();

	glClearColor(color.x, color.y, color.z, 1.0f);
}

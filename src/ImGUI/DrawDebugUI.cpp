#include "DrawDebugUI.hpp"

void Patata::Engine::EngineImpl::DrawDebugUI(void) {
	static ImVec4 color = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
	static bool firstpass = true;

	if (firstpass) {
		firstpass = false;
		if (*RaccoonRenderer->Backend == Patata::Graphics::Backend::Vulkan) {
		}
		else {
			color = ImVec4(0.113f, 0.578f, 0.810f, 1.0f);
		}
	}

	ImGui::SetNextWindowSize(ImVec2(500, 300));
	ImGui::Begin("Patata Engine | (Debug) Development", nullptr, 0);
	ImGui::BeginTabBar("Tools"); {
		ImGui::BeginTabItem("Tools"); {
			ImGui::ColorEdit3("Buffer Color", reinterpret_cast<float *>(&color));
			ImGui::Separator();
			ImGui::EndTabItem();
		}
		ImGui::EndTabBar();
	}
	ImGui::End();

	ImGui::Begin("Window Test", nullptr, 0);
	ImGui::End();

	glClearColor(color.x, color.y, color.z, 1.0f);
}

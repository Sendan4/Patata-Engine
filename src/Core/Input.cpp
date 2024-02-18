#include <SDL.h>

#if defined(DEBUG)
#include <imgui_impl_sdl2.h>
#endif

#ifndef YAML_CPP_API
#define YAML_CPP_API
#endif
#include <yaml-cpp/yaml.h>
#include <SDL.h>
#include <vulkan/vulkan.hpp>

// Patata Engine
#include "PatataEngine/PatataEngine.hpp"

void Patata::Engine::HandleEvent(SDL_Event & Event) {
	static bool PatataKeyPress = false;
	static bool PatataFullScreen = false;
		
	#if defined(DEBUG)
	if (*RaccoonRenderer->Backend == Patata::Graphics::Backend::OpenGL)
		ImGui_ImplSDL2_ProcessEvent(&Event);
	#endif

	switch (Event.type) {
		case SDL_KEYDOWN:
			if (!PatataKeyPress) {
				switch (Event.key.keysym.sym) {
					case SDLK_F11:
						if (!PatataFullScreen) {
							PatataFullScreen = true;
							SDL_SetWindowFullscreen(GameWindow, SDL_WINDOW_FULLSCREEN);
						}
						else {
							PatataFullScreen = false;
							SDL_SetWindowFullscreen(GameWindow, 0);
						}
						break;
				}
				PatataKeyPress = true;
			}
			break;

		case SDL_KEYUP:
			if (PatataKeyPress)
				PatataKeyPress = false;
			break;
	}
}

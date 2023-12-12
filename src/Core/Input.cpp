#include <SDL.h>

#if defined(DEBUG)
#include <imgui_impl_sdl2.h>
#endif

// Patata Engine
#include "PatataEngine/PatataEngine.hpp"

void Patata::Engine::HandleEvent(SDL_Event & Event) {
	static bool KeyPress = false;
	static bool FullScreen = false;
		
	#if defined(DEBUG)
	if (bGraphicsAPI == Patata::GraphicsAPI::OpenGL)
		ImGui_ImplSDL2_ProcessEvent(&Event);
	#endif

	switch (Event.type) {
		case SDL_KEYDOWN:
			if (!KeyPress) {
				switch (Event.key.keysym.sym) {
					case SDLK_F11:
						if (!FullScreen) {
							FullScreen = true;
							SDL_SetWindowFullscreen(Info->pWindow, SDL_WINDOW_FULLSCREEN);
						}
						else {
							FullScreen = false;
							SDL_SetWindowFullscreen(Info->pWindow, 0);
						}
						break;
				}
				KeyPress = true;
			}
			break;

		case SDL_KEYUP:
			if (KeyPress)
				KeyPress = false;
			break;
	}
}

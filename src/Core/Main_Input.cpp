#include <SDL.h>

#if defined(DEBUG)
#include <imgui.h>
#include <backends/imgui_impl_sdl2.h>
#endif

// Patata Engine
#include "Patata_Engine/Patata_Engine.hpp"

bool Patata::PatataEngine::MainInput(void) {
	static bool KeyPress = false;
	static bool FullScreen = false;

	while (SDL_PollEvent(MainEvent)) {
		#if defined(DEBUG)
		if (!bGraphicsAPI)
			ImGui_ImplSDL2_ProcessEvent(MainEvent);
		#endif

		switch (MainEvent->type) {
			case SDL_QUIT: return false; break;

			case SDL_KEYDOWN:
				if (!KeyPress) {
					switch (MainEvent->key.keysym.sym) {
						case SDLK_F11:
							if (!FullScreen) {
								FullScreen = true;
								SDL_SetWindowFullscreen(pWindow->WindowGet(), SDL_WINDOW_FULLSCREEN);
							}
							else {
								FullScreen = false;
								SDL_SetWindowFullscreen(pWindow->WindowGet(), 0);
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

	return true;
}

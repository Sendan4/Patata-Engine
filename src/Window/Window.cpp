#include <SDL.h>

#include "PatataEngine/PatataEngine.hpp"
#include "Log.hpp"
#include "TerminalColors.hpp"

#if defined(PATATA_GAME_NAME)
	#define PATATA_GAME_ICON_FILE PATATA_GAME_NAME ".bmp"
#else
	#if defined(DEBUG)
		#define PATATA_GAME_ICON_FILE "icon-debug.bmp"
	#else
		#define PATATA_GAME_ICON_FILE "icon-release.bmp"
	#endif
#endif

void Patata::Engine::CreateGameWindow(const std::string & Title, const uint32_t & WindowWidth, const uint32_t & WindowHeight) {
	std::string PatataWindowTitle;

	if (!Title.empty())
		#if defined(DEBUG)
		PatataWindowTitle = Title + " | Debug (Development)";
		#else
		PatataWindowTitle = Title;
		#endif
	else {
		#if defined(PATATA_GAME_NAME)
			#if defined(DEBUG)
				PatataWindowTitle = PATATA_GAME_NAME;
				PatataWindowTitle += " | Debug (Development)";
			#else
				PatataWindowTitle = PATATA_GAME_NAME;
			#endif
		#else
			#if defined(DEBUG)
				PatataWindowTitle = "Patata Engine | Debug (Development)";
			#else
				PatataWindowTitle = "Patata Engine";
			#endif
		#endif
	}

	uint32_t flags = 0;

	if (bGraphicsAPI)
		flags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_VULKAN | SDL_WINDOW_ALLOW_HIGHDPI;
	else flags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI; 

    GameWindow = SDL_CreateWindow(
		PatataWindowTitle.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
    	WindowWidth, WindowHeight,
        flags);
}

void Patata::Engine::SetWindowIcon(void) {
	SDL_Surface * Icon = SDL_LoadBMP(PATATA_GAME_ICON_FILE);
	SDL_SetWindowIcon(GameWindow, Icon);
	SDL_FreeSurface(Icon);
}

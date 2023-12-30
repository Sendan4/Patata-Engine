#include "PatataEngine/PatataEngine.hpp"
#include "Log.hpp"
#include "TerminalColors.hpp"

uint64_t Patata::Engine::GetWindowFlags(void) {
	uint32_t flags = 0;

	if (bGraphicsAPI)
		flags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_VULKAN;
	else flags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL; 
		
	return flags;
}

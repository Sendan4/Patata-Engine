#include <SDL.h>
#include <fast_io.h>

// Patata Engine
#include "PatataEngine/Log.hpp"
#include "PatataEngine/TerminalColors.hpp"

void Patata::Log::WindowIconSetStatus(SDL_Surface * WINDOW_ICON) {
	if (WINDOW_ICON != nullptr)
		fast_io::io::println(Bold, "    Icon                    : ", Reset, Chartreuse1, "Yes", Reset, "\n");
	else {
		fast_io::io::println(Bold, "    Icon                    : ", Reset, BLightGoldenRod1, "No", Reset);
	}
}

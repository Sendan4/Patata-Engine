#include <iostream>
#include <iomanip>
#include <ios>
#include <cstring>

#include <SDL.h>

// Patata Engine
#include "PatataEngine/Log.hpp"
#include "PatataEngine/TerminalColors.hpp"

void Patata::Log::WindowIconSetStatus(SDL_Surface * WINDOW_ICON) {
	if (WINDOW_ICON != nullptr) 
		std::cout << Bold << std::setw(4) << ' ' << "Icon" << std::setw(22) << ": " << Reset << Chartreuse1  << "Yes\n\n" << Reset;
	else {
		std::cout << Bold << std::setw(4) << ' ' << "Icon" << std::setw(22) << ": " << Reset << BLightGoldenRod1 << "NO\n\n" << Reset;
		std::cout << "\n" << BLightGoldenRod1 << SDL_GetError() << Reset << "\n\n";
	}
}

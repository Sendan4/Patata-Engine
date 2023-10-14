#include <iostream>
#include <iomanip>
#include <cstring>

#include <SDL.h>
#include <windows.h>

// Patata Engine
#include "PatataEngine/Log.hpp"

void Patata::Log::WindowIconSetStatus(SDL_Surface * WINDOW_ICON) {
	HANDLE Terminal = GetStdHandle(STD_OUTPUT_HANDLE);

	if (WINDOW_ICON != nullptr) {
		std::cout << std::setw(4) << ' ' << "Icon" << std::setw(22) << ": ";
		SetConsoleTextAttribute(Terminal, 10);
		std::cout << "Yes\n";
		SetConsoleTextAttribute(Terminal, 7);

		std::cout << "\n";
	}
	else {
		std::cout << std::setw(4) << ' ' << "Icon" << std::setw(22) << ": ";
		SetConsoleTextAttribute(Terminal, 14);
		std::cout << "No\n";
		SetConsoleTextAttribute(Terminal, 12);
		std::cout << SDL_GetError() << "\n";
		SetConsoleTextAttribute(Terminal, 7);

		std::cout << "\n";
	}
}

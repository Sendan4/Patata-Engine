#include <cstring>

#include <fast_io.h>
#include <SDL.h>
#include <windows.h>

// Patata Engine
#include "PatataEngine/Log.hpp"

void Patata::Log::WindowIconSetStatus(SDL_Surface * WINDOW_ICON) {
	HANDLE Terminal = GetStdHandle(STD_OUTPUT_HANDLE);

	if (WINDOW_ICON != nullptr) {
		fast_io::io::print(fast_io::out(), "    Icon                    : ");
		SetConsoleTextAttribute(Terminal, 10);
		fast_io::io::println(fast_io::out(), "Yes");
		SetConsoleTextAttribute(Terminal, 7);

		fast_io::io::println(fast_io::out(), "");
	}
	else {
		fast_io::io::print(fast_io::out(), "    Icon                    : ");
		SetConsoleTextAttribute(Terminal, 14);
		fast_io::io::println(fast_io::out(), "No");
		SetConsoleTextAttribute(Terminal, 7);

		fast_io::io::println(fast_io::out(), "");
	}
}

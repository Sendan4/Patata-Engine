#include <cstring>
#if defined(__GNUC__) || defined(__MINGW64__)
#include <cxxabi.h>
#endif

#include <fast_io.h>
#include <SDL.h>
#include <SDL_syswm.h>
#include <windows.h>

// Patata Engine
#include "Log.hpp"

void Patata::Log::WindowLog(SDL_Window * Window) {
	HANDLE Terminal = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(Terminal, FOREGROUND_INTENSITY);
	#if defined(__GNUC__) || defined(__MINGW64__)	
		fast_io::io::print(fast_io::out(), "[", std::string_view{ abi::__cxa_demangle(typeid(Window).name(), nullptr, nullptr, nullptr) }, "] ");
	#else
		fast_io::io::print(fast_io::out(), "[", std::string_view{ typeid(Window).name() }, "] ");
	#endif

	SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN);
	fast_io::io::print(fast_io::out(), "Window ");
	SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	fast_io::io::println(fast_io::out(), "INFO :");
	SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

	SDL_SysWMinfo WindowInfo;
	SDL_VERSION(&WindowInfo.version);
	SDL_GetWindowWMInfo(Window, &WindowInfo);
	
	switch(WindowInfo.subsystem) {
		case SDL_SYSWM_WINDOWS:
			SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
			fast_io::io::print(fast_io::out(), "  Window System : ");
			SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			fast_io::io::println(fast_io::out(), "Windows");

			SetConsoleTextAttribute(Terminal, FOREGROUND_INTENSITY);
			#if defined(__GNUC__) || defined(__MINGW64__)	
				fast_io::io::print(fast_io::out(), "  [", std::string_view{ abi::__cxa_demangle(typeid(WindowInfo.info.win.window).name(), nullptr, nullptr, nullptr) }, "]");
			#else
				fast_io::io::print(fast_io::out(), "  [", std::string_view{ typeid(WindowInfo.info.win.window).name() }, "]");
			#endif

			SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
			fast_io::io::println(fast_io::out(), " Window Type\n");
			SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			break;

		case SDL_SYSWM_WINRT:
			SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
			fast_io::io::print(fast_io::out(), "  Window System : ");
			SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			fast_io::io::println(fast_io::out(), "WinRT");
			break;

		default : case SDL_SYSWM_UNKNOWN:
			SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
			fast_io::io::print(fast_io::out(), "  Window System : ");
			SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			fast_io::io::println(fast_io::out(), "Unknown");
			break;
	}
}

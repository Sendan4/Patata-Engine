#include <fast_io.h>
#include <SDL.h>

#include "PatataEngine/Log.hpp"
#if defined(_WIN64)
	#include <windows.h>
#else
	#include "PatataEngine/TerminalColors.hpp"
#endif

void Patata::Log::FatalErrorMessage(std::string TITLE, std::string MESSAGE, YAML::Node CONFIG) {
	if (CONFIG["show-fatal-error-messagebox"].as<bool>())
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, TITLE.c_str(), MESSAGE.c_str(), nullptr);
	else
	#if defined(_WIN64)
	{
		HANDLE Terminal = GetStdHandle(STD_OUTPUT_HANDLE);

		SetConsoleTextAttribute(Terminal, 12);
		fast_io::io::perr("ERROR FATAL: ");
		SetConsoleTextAttribute(Terminal, 7);
		fast_io::io::perrln(MESSAGE, "\n");
	}
	#else
		fast_io::io::perrln(Bold, CSalmon1, "ERROR FATAL: ", Reset, MESSAGE, "\n");
	#endif
}

void Patata::Log::ErrorMessage(std::string MESSAGE) {
	#if defined(_WIN64)
		HANDLE Terminal = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(Terminal, 12);
		fast_io::io::perr("ERROR: ");
		SetConsoleTextAttribute(Terminal, 7);

		fast_io::io::perrln(MESSAGE, "\n");
	#else
		fast_io::io::perrln(Bold, CSalmon1, "ERROR: ", Reset, MESSAGE, "\n");
	#endif
}

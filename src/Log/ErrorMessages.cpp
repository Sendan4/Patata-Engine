#include <fast_io.h>

#if defined(_WIN64)
	#include <windows.h>
#endif

#include "Log.hpp"
#include "TerminalColors.hpp"

void Patata::Log::FatalErrorMessage(const std::string & Title, const std::string & Message, YAML::Node & CONFIG) {
	std::string PatataErrorTitle = "Patata Engine - ";
	PatataErrorTitle += Title;

	if (CONFIG["patata-engine"]["show-fatal-error-messagebox"].as<bool>())
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, PatataErrorTitle.c_str(), Message.c_str(), nullptr);
	else
	#if defined(_WIN64)
	{
		HANDLE Terminal = GetStdHandle(STD_OUTPUT_HANDLE);
		DWORD mode = 0;
		GetConsoleMode(Terminal, &mode);
		SetConsoleMode(Terminal, ENABLE_VIRTUAL_TERMINAL_PROCESSING | mode);

		fast_io::io::perr(fast_io::out(), "ERROR FATAL : " , Message);

		SetConsoleMode(Terminal, mode);
	}
	#else
		fast_io::io::perrln(PATATA_TERM_BOLD, PATATA_TERM_COLOR_RED, "ERROR FATAL : ", PATATA_TERM_RESET, Message);
	#endif
}

void Patata::Log::ErrorMessage(const std::string & Message) {
	#if defined(_WIN64)
		HANDLE Terminal = GetStdHandle(STD_OUTPUT_HANDLE);
		DWORD mode = 0;
		GetConsoleMode(Terminal, &mode);
		SetConsoleMode(Terminal, ENABLE_VIRTUAL_TERMINAL_PROCESSING | mode);

		fast_io::io::perr(fast_io::out(), "ERROR FATAL : " , Message);

		SetConsoleMode(Terminal, mode);
	#else
		fast_io::io::perrln(PATATA_TERM_BOLD, PATATA_TERM_COLOR_RED, "ERROR : ", PATATA_TERM_RESET, Message);
	#endif
}

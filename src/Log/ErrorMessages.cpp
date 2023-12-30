#include <fast_io.h>

#include "Log.hpp"
#if defined(_WIN64)
	#include <windows.h>
#else
	#include "TerminalColors.hpp"
#endif

void Patata::Log::FatalErrorMessage(const std::string & Title, const std::string & Message, YAML::Node & CONFIG) {
	std::string PatataErrorTitle = "Patata Engine - ";
	PatataErrorTitle += Title;

	if (CONFIG["patata-engine"]["show-fatal-error-messagebox"].as<bool>())
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, PatataErrorTitle.c_str(), Message.c_str(), nullptr);
	else
	#if defined(_WIN64)
	{
		HANDLE Terminal = GetStdHandle(STD_OUTPUT_HANDLE);

		SetConsoleTextAttribute(Terminal, 12);
		fast_io::io::perr(fast_io::out(), "ERROR FATAL: ");
		SetConsoleTextAttribute(Terminal, 7);
		fast_io::io::perrln(fast_io::out(), Message);
	}
	#else
		fast_io::io::perrln(Bold, FindianRed1, "ERROR FATAL: ", Reset, Message);
	#endif
}

void Patata::Log::ErrorMessage(const std::string & Message) {
	#if defined(_WIN64)
		HANDLE Terminal = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(Terminal, 12);
		fast_io::io::perr(fast_io::out(), "ERROR: ");
		SetConsoleTextAttribute(Terminal, 7);

		fast_io::io::perrln(fast_io::out(), Message);
	#else
		fast_io::io::perrln(Bold, FindianRed1, "ERROR: ", Reset, Message);
	#endif
}

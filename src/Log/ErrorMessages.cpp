#include <fast_io.h>

#include "Log.hpp"
#if defined(_WIN64)
	#include <windows.h>
#else
	#include "TerminalColors.hpp"
#endif

void Patata::Log::FatalErrorMessage(const std::string & Title, const std::string & Message, YAML::Node CONFIG) {
	if (CONFIG["show-fatal-error-messagebox"].as<bool>())
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, Title.c_str(), Message.c_str(), nullptr);
	else
	#if defined(_WIN64)
	{
		HANDLE Terminal = GetStdHandle(STD_OUTPUT_HANDLE);

		SetConsoleTextAttribute(Terminal, 12);
		fast_io::io::perr("ERROR FATAL: ");
		SetConsoleTextAttribute(Terminal, 7);
		fast_io::io::perrln(Message, "\n");
	}
	#else
		fast_io::io::perrln(Bold, CSalmon1, "ERROR FATAL: ", Reset, Message, "\n");
	#endif
}

void Patata::Log::ErrorMessage(const std::string & Message) {
	#if defined(_WIN64)
		HANDLE Terminal = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(Terminal, 12);
		fast_io::io::perr("ERROR: ");
		SetConsoleTextAttribute(Terminal, 7);

		fast_io::io::perrln(Message, "\n");
	#else
		fast_io::io::perrln(Bold, CSalmon1, "ERROR: ", Reset, Message, "\n");
	#endif
}

#if defined(GAME_NAME)
	#define GAME_CONFIG_FILE_NAME GAME_NAME ".yaml"
#endif

#include <fast_io.h>

#include "Log.hpp"
#if defined(_WIN64)
	#include <windows.h>
#else
	#include "TerminalColors.hpp"
#endif

void Patata::Log::YamlFileErrorMessage(void) {
	#if defined(_WIN64)
		HANDLE Terminal = GetStdHandle(STD_OUTPUT_HANDLE);

		SetConsoleTextAttribute(Terminal, 12);
		fast_io::io::perr("\nERROR FATAL: ");
		SetConsoleTextAttribute(Terminal, 7);
	#else
		fast_io::io::perr("\n", Bold, CSalmon1, "Error Fatal: ", Reset);
	#endif

	#if defined(GAME_NAME)
		fast_io::io::perrln("Cannot find ", GAME_CONFIG_FILE_NAME, " file");
		{
			std::string errMessage = "Cannot find ";
	 		errMessage += GAME_CONFIG_FILE_NAME;
			errMessage += " file";
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Missing Config File", errMessage.c_str(), nullptr);
		}
	#else
		fast_io::io::perrln("Cannot find patata.yaml file");

		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Config File", "Cannot find patata.yaml", nullptr);
	#endif
}

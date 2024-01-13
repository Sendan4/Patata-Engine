// OS
#if __linux__ && !__ANDROID__
#	define PATATA_OS "Linux"
#elif _WIN64 || _WIN32
#	define PATATA_OS "Windows"
#endif

// Compiler
#if __GNUC__
#	if __clang__
#		define PATATA_COMPILER "Clang"	
#	elif __MINGW64__
#		define PATATA_COMPILER "MinGW"
#	else
#		define PATATA_COMPILER "GCC"
#	endif
#elif _MSC_VER <= 1929
#	define PATATA_COMPILER "Old Microsoft Visual C++ (MSVC)"
#elif _MSC_VER >= 1930
#	define PATATA_COMPILER "Microsoft Visual C++ (MSVC)"
#endif

#if defined(__GNUC__) || defined(__MINGW64__)
#include <cxxabi.h>
#endif

#include <fast_io.h>
#include <windows.h>

// Patata Engine
#include "PatataEngine/PatataEngine.hpp"
#include "Log.hpp"
#include "TerminalColors.hpp"

void Patata::Log::StartPatataLogInfo(void) {
	HANDLE Terminal = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD mode = 0;
	GetConsoleMode(Terminal, &mode);
	SetConsoleMode(Terminal, ENABLE_VIRTUAL_TERMINAL_PROCESSING | mode);
	UINT defaultOutputCP = GetConsoleOutputCP();
	SetConsoleOutputCP(CP_UTF8);

	fast_io::io::println(fast_io::out(), PATATA_TERM_COLOR_PATATA, PATATA_ENGINE_NAME, PATATA_TERM_COLOR_WHITE, " INFO : ");
	
	#if defined(PATATA_GIT_BRANCH)
	fast_io::io::println(fast_io::out(), PATATA_TERM_COLOR_WHITE, "  Git Branch : ", PATATA_TERM_COLOR_GRAY1, PATATA_GIT_BRANCH, " ");
	#endif

	#if defined(PATATA_GIT_HASH_LONG)
		fast_io::io::print(fast_io::out(), PATATA_TERM_COLOR_WHITE, "  Git Commit Hash Long : ", PATATA_TERM_COLOR_GRAY1, PATATA_GIT_HASH_LONG, " ");

		#if defined(PATATA_GIT_WORK_DIR_IS_CLEAN)
			#if PATATA_GIT_WORK_DIR_IS_CLEAN_BOOL == 1
				fast_io::io::print(fast_io::out(), PATATA_TERM_COLOR_GREEN);
			#else
				fast_io::io::print(fast_io::out(), PATATA_TERM_COLOR_YELLOW);
			#endif
		fast_io::io::print(fast_io::out(), PATATA_GIT_WORK_DIR_IS_CLEAN);
		#endif

		#if defined(PATATA_GIT_WORK_DIR_IS_STAGED)
			fast_io::io::print(fast_io::out(), PATATA_TERM_RESET, " | ");

			#if PATATA_GIT_WORK_DIR_IS_STAGED_BOOL == 1
				fast_io::io::print(fast_io::out(), PATATA_TERM_COLOR_GREEN);
			#else
				fast_io::io::print(fast_io::out(), PATATA_TERM_COLOR_YELLOW);
			#endif
			fast_io::io::print(fast_io::out(), PATATA_GIT_WORK_DIR_IS_STAGED);
		#endif

		fast_io::io::println(fast_io::out());
	#endif

	#if defined(PATATA_GIT_HASH_SHORT)
		fast_io::io::print(fast_io::out(), PATATA_TERM_COLOR_WHITE, "  Git Commit Hash Short : ", PATATA_TERM_COLOR_GRAY1, PATATA_GIT_HASH_SHORT, " ");

		#if defined(PATATA_GIT_WORK_DIR_IS_CLEAN)
			#if PATATA_GIT_WORK_DIR_IS_CLEAN_BOOL == 1
				fast_io::io::print(fast_io::out(), PATATA_TERM_COLOR_GREEN);
			#else
				fast_io::io::print(fast_io::out(), PATATA_TERM_COLOR_YELLOW);
			#endif
		fast_io::io::print(fast_io::out(), PATATA_GIT_WORK_DIR_IS_CLEAN);
		#endif

		#if defined(PATATA_GIT_WORK_DIR_IS_STAGED)
			fast_io::io::print(fast_io::out(), PATATA_TERM_RESET, " | ");

			#if PATATA_GIT_WORK_DIR_IS_STAGED_BOOL == 1
				fast_io::io::print(fast_io::out(), PATATA_TERM_COLOR_GREEN);
			#else
				fast_io::io::print(fast_io::out(), PATATA_TERM_COLOR_YELLOW);
			#endif
			fast_io::io::print(fast_io::out(), PATATA_GIT_WORK_DIR_IS_STAGED);
		#endif

		fast_io::io::println(fast_io::out());
	#endif

	fast_io::io::println(fast_io::out(), PATATA_TERM_COLOR_WHITE, "  Build Date : ", PATATA_TERM_COLOR_GRAY1, __DATE__, " ", __TIME__);

	fast_io::io::println(fast_io::out(), PATATA_TERM_COLOR_WHITE, "  Version : ", PATATA_TERM_COLOR_GRAY1, PATATA_ENGINE_VERSION);

	fast_io::io::println(fast_io::out(),
		PATATA_TERM_COLOR_WHITE,
		"  Compiler : ",
		PATATA_TERM_COLOR_GRAY0,
		"[" , PATATA_COMPILER_PROGRAM, "]",
		PATATA_TERM_COLOR_GRAY1,
		" ", PATATA_COMPILER,
		" ", PATATA_COMPILER_VERSION);

	fast_io::io::print(fast_io::out(), PATATA_TERM_COLOR_WHITE, "  Build System : ", PATATA_TERM_COLOR_GRAY0, "[" , PATATA_BUILD_SYSTEM_GENERATOR);
	#if defined(PATATA_BUILD_SYSTEM_GENERATOR_VERSION)
		fast_io::io::print(fast_io::out() , " ", PATATA_BUILD_SYSTEM_GENERATOR_VERSION, "] ");
	#else
		fast_io::io::print(fast_io::out() , "] ");
	#endif
	fast_io::io::println(fast_io::out(), PATATA_TERM_COLOR_GRAY1, PATATA_BUILD_SYSTEM, " ", PATATA_BUILD_SYSTEM_VERSION);

	fast_io::io::println(fast_io::out(), PATATA_TERM_COLOR_WHITE, "  Build Type : ", PATATA_TERM_COLOR_GRAY1, PATATA_BUILD_TYPE);

	fast_io::io::println(fast_io::out(), PATATA_TERM_COLOR_WHITE, "  Operating System : ", PATATA_TERM_COLOR_GRAY1, PATATA_OS);

	fast_io::io::println(fast_io::out(), PATATA_TERM_COLOR_WHITE, "  CPU Architecture Type : ", PATATA_TERM_COLOR_GRAY1, PATATA_ARCH);

	#if defined(PATATA_FAST_IO_GIT_COMMIT_HASH_SHORT)
	fast_io::io::println(fast_io::out(), PATATA_TERM_COLOR_WHITE, "  Fast IO Git Commit Hash Short : ", PATATA_TERM_COLOR_GRAY1, PATATA_FAST_IO_GIT_COMMIT_HASH_SHORT);
	#endif
	{
		SDL_version sdlversion;
		SDL_VERSION(&sdlversion);

		fast_io::io::println(fast_io::out(),
			PATATA_TERM_COLOR_WHITE,
			"  SDL Version : ",
			PATATA_TERM_COLOR_GRAY1,
			sdlversion.major, ".", sdlversion.minor, ".", sdlversion.patch);
	}

	#if defined(PATATA_YAML_CPP_VERSION)
	fast_io::io::println(fast_io::out(), PATATA_TERM_COLOR_WHITE, "  Yaml-Cpp Version : ", PATATA_TERM_COLOR_GRAY1, PATATA_YAML_CPP_VERSION);
	#endif
	
	#if defined(PATATA_GAME_NAME)
	fast_io::io::println(fast_io::out(), PATATA_TERM_COLOR_WHITE, "  Game Name : ", PATATA_TERM_COLOR_GRAY1, PATATA_GAME_NAME);
	#endif

	SetConsoleOutputCP(defaultOutputCP);
	fast_io::io::println(fast_io::out(), PATATA_TERM_RESET);
	SetConsoleMode(Terminal, mode);
}

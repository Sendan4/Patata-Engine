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

void Patata::Log::StartPatataLogInfo(void) {
	HANDLE Terminal = GetStdHandle(STD_OUTPUT_HANDLE);
	UINT defaultOutputCP = GetConsoleOutputCP();
	SetConsoleOutputCP(CP_UTF8);

	SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN);
	fast_io::io::print(fast_io::out(), PATATA_ENGINE_NAME);
	SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	fast_io::io::println(fast_io::out(), " INFO : ");
	SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	
	#if defined(PATATA_GIT_BRANCH)
	SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	fast_io::io::print(fast_io::out(), "  Git Branch : ");
	SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	fast_io::io::println(fast_io::out(), PATATA_GIT_BRANCH, " ");
	#endif

	#if defined(PATATA_GIT_HASH_LONG)
		SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		fast_io::io::print(fast_io::out(), "  Git Commit Hash Long : ");
		SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		fast_io::io::print(fast_io::out(), PATATA_GIT_HASH_LONG, " ");

		#if defined(PATATA_GIT_WORK_DIR_IS_CLEAN)
			#if PATATA_GIT_WORK_DIR_IS_CLEAN_BOOL == 1
				SetConsoleTextAttribute(Terminal, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			#else
				SetConsoleTextAttribute(Terminal,FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			#endif
		fast_io::io::print(fast_io::out(), PATATA_GIT_WORK_DIR_IS_CLEAN);
		#endif

		#if defined(PATATA_GIT_WORK_DIR_IS_STAGED)
			SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			fast_io::io::print(fast_io::out(), " | ");

			#if PATATA_GIT_WORK_DIR_IS_STAGED_BOOL == 1
				SetConsoleTextAttribute(Terminal, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			#else
				SetConsoleTextAttribute(Terminal,FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			#endif
			fast_io::io::print(fast_io::out(), PATATA_GIT_WORK_DIR_IS_STAGED);
		#endif

		fast_io::io::println(fast_io::out());
	#endif

	#if defined(PATATA_GIT_HASH_SHORT)
		SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		fast_io::io::print(fast_io::out(), "  Git Commit Hash Short : ");
		SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		fast_io::io::print(fast_io::out(), PATATA_GIT_HASH_SHORT, " ");

		#if defined(PATATA_GIT_WORK_DIR_IS_CLEAN)
			#if PATATA_GIT_WORK_DIR_IS_CLEAN_BOOL == 1
				SetConsoleTextAttribute(Terminal, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			#else
				SetConsoleTextAttribute(Terminal,FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			#endif
		fast_io::io::print(fast_io::out(), PATATA_GIT_WORK_DIR_IS_CLEAN);
		#endif

		#if defined(PATATA_GIT_WORK_DIR_IS_STAGED)
			SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			fast_io::io::print(fast_io::out(), " | ");

			#if PATATA_GIT_WORK_DIR_IS_STAGED_BOOL == 1
				SetConsoleTextAttribute(Terminal, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			#else
				SetConsoleTextAttribute(Terminal,FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			#endif
			fast_io::io::print(fast_io::out(), PATATA_GIT_WORK_DIR_IS_STAGED);
		#endif

		fast_io::io::println(fast_io::out());
	#endif

	SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	fast_io::io::print(fast_io::out(), "  Build Date : ");
	SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	fast_io::io::println(fast_io::out(), __DATE__, " ", __TIME__);

	SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	fast_io::io::print(fast_io::out(), "  Version : ");
	SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	fast_io::io::println(fast_io::out(), PATATA_ENGINE_VERSION);

	SetConsoleTextAttribute(Terminal, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	fast_io::io::print(fast_io::out(), "  Compiler : ");
	SetConsoleTextAttribute(Terminal, FOREGROUND_INTENSITY);
	fast_io::io::print(fast_io::out() , "[" , PATATA_COMPILER_PROGRAM, "]");
	SetConsoleTextAttribute(Terminal, 7);
	fast_io::io::println(fast_io::out(), " ", PATATA_COMPILER, " ", PATATA_COMPILER_VERSION);

	SetConsoleTextAttribute(Terminal, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	fast_io::io::print(fast_io::out(), "  Build System : ");
	SetConsoleTextAttribute(Terminal, FOREGROUND_INTENSITY);
	fast_io::io::print(fast_io::out() , "[" , PATATA_BUILD_SYSTEM_GENERATOR);
	#if defined(PATATA_BUILD_SYSTEM_GENERATOR_VERSION)
		fast_io::io::print(fast_io::out() , " ", PATATA_BUILD_SYSTEM_GENERATOR_VERSION, "] ");
	#else
		fast_io::io::print(fast_io::out() , "] ");
	#endif
	SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	fast_io::io::println(fast_io::out(), PATATA_BUILD_SYSTEM, " ", PATATA_BUILD_SYSTEM_VERSION);

	SetConsoleTextAttribute(Terminal, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	fast_io::io::print(fast_io::out(), "  Build Type : ");
	SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	fast_io::io::println(fast_io::out(), PATATA_BUILD_TYPE);

	SetConsoleTextAttribute(Terminal, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	fast_io::io::print(fast_io::out(), "  Operating System : ");
	SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	fast_io::io::println(fast_io::out(), PATATA_OS);

	SetConsoleTextAttribute(Terminal, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	fast_io::io::print(fast_io::out(), "  CPU Architecture Type : ");
	SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	fast_io::io::println(fast_io::out(), PATATA_ARCH);

	#if defined(PATATA_FAST_IO_GIT_COMMIT_HASH_SHORT)
	SetConsoleTextAttribute(Terminal, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	fast_io::io::print(fast_io::out(), "  Fast IO Git Commit Hash Short : ");
	SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	fast_io::io::println(fast_io::out(), PATATA_FAST_IO_GIT_COMMIT_HASH_SHORT);
	#endif

	{
		SDL_version sdlversion;
		SDL_VERSION(&sdlversion);

		SetConsoleTextAttribute(Terminal, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		fast_io::io::print(fast_io::out(), "  SDL Version : ");
		SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		fast_io::io::println(fast_io::out(), sdlversion.major, ".", sdlversion.minor, ".", sdlversion.patch);
	}

	#if defined(PATATA_YAML_CPP_VERSION)
	SetConsoleTextAttribute(Terminal, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	fast_io::io::print(fast_io::out(), "  Yaml-Cpp Version : ");
	SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	fast_io::io::println(fast_io::out(), PATATA_YAML_CPP_VERSION);
	#endif
	
	#if defined(PATATA_GAME_NAME)
	SetConsoleTextAttribute(Terminal, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	fast_io::io::print(fast_io::out(), "  Game Name : ");
	SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	fast_io::io::println(fast_io::out(), PATATA_GAME_NAME);
	#endif

	SetConsoleOutputCP(defaultOutputCP);
	fast_io::io::println(fast_io::out());
}

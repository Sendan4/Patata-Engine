// OS
#if __linux__ && !__ANDROID__
	#define PATATA_OS "Linux"
#elif _WIN64 || _WIN32
	#define PATATA_OS "Windows"
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

#include <fast_io.h>

// Patata Engine
#include "Log.hpp"
#include "TerminalColors.hpp"

void Patata::Log::StartPatataLogInfo(void) {
	fast_io::io::println(PATATA_TERM_COLOR_PATATA,
			PATATA_TERM_BOLD,
			PATATA_ENGINE_NAME,
			PATATA_TERM_RESET,
			" INFO");
	
	#if defined(PATATA_GIT_BRANCH)
		fast_io::io::println(PATATA_TERM_BOLD, "  Git Branch : ", PATATA_TERM_RESET, PATATA_GIT_BRANCH);
	#endif

	#if defined(PATATA_GIT_HASH_LONG)
		fast_io::io::print(PATATA_TERM_BOLD,
				"  Git Commit Hash Long : ",
				PATATA_TERM_RESET,
				PATATA_GIT_HASH_LONG);

		#if defined(PATATA_GIT_WORK_DIR_IS_CLEAN)
			#if PATATA_GIT_WORK_DIR_IS_CLEAN_BOOL == 1
				fast_io::io::print(PATATA_TERM_COLOR_GREEN);
			#else
				fast_io::io::print(PATATA_TERM_COLOR_YELLOW);
			#endif
			fast_io::io::print(" ", PATATA_GIT_WORK_DIR_IS_CLEAN);
		#endif

		#if defined(PATATA_GIT_WORK_DIR_IS_STAGED)
			fast_io::io::print(PATATA_TERM_RESET, " | ");

			#if PATATA_GIT_WORK_DIR_IS_STAGED_BOOL == 1
				fast_io::io::print(PATATA_TERM_COLOR_GREEN);
			#else
				fast_io::io::print(PATATA_TERM_COLOR_YELLOW);
			#endif
	
			fast_io::io::print(PATATA_GIT_WORK_DIR_IS_STAGED);
		#endif

		fast_io::io::println(PATATA_TERM_RESET);
	#endif

	#if defined(PATATA_GIT_HASH_SHORT)
		fast_io::io::print(PATATA_TERM_BOLD,
			"  Git Commit Hash Short : ",
			PATATA_TERM_RESET,
			PATATA_GIT_HASH_SHORT);

		#if defined(PATATA_GIT_WORK_DIR_IS_CLEAN)
			#if PATATA_GIT_WORK_DIR_IS_CLEAN_BOOL == 1
				fast_io::io::print(PATATA_TERM_COLOR_GREEN);
			#else
				fast_io::io::print(PATATA_TERM_COLOR_YELLOW);
			#endif
			fast_io::io::print(" ", PATATA_GIT_WORK_DIR_IS_CLEAN);
		#endif

		#if defined(PATATA_GIT_WORK_DIR_IS_STAGED)
			fast_io::io::print(PATATA_TERM_RESET, " | ");

			#if PATATA_GIT_WORK_DIR_IS_STAGED_BOOL == 1
				fast_io::io::print(PATATA_TERM_COLOR_GREEN);
			#else
				fast_io::io::print(PATATA_TERM_COLOR_YELLOW);
			#endif
	
			fast_io::io::print(PATATA_GIT_WORK_DIR_IS_STAGED);
		#endif

		fast_io::io::println(PATATA_TERM_RESET);
	#endif

	fast_io::io::println(PATATA_TERM_BOLD,
			"  Build Date : ",
			PATATA_TERM_RESET,
			__DATE__, " ", __TIME__);

	fast_io::io::println(PATATA_TERM_BOLD,
			"  Version : ",
			PATATA_TERM_RESET,
			PATATA_ENGINE_VERSION);

	fast_io::io::println(PATATA_TERM_BOLD,
			"  Compiler : ",
			PATATA_TERM_DIM,
			PATATA_TERM_COLOR_GRAY0,
			"[", PATATA_COMPILER_PROGRAM, "] ",
			PATATA_TERM_RESET,
			PATATA_COMPILER, " ", PATATA_COMPILER_VERSION);

	fast_io::io::println(PATATA_TERM_BOLD,
			"  Build System : ",
			PATATA_TERM_DIM,
			PATATA_TERM_COLOR_GRAY0,
			"[" , PATATA_BUILD_SYSTEM_GENERATOR, " ", PATATA_BUILD_SYSTEM_GENERATOR_VERSION, "] ",
			PATATA_TERM_RESET,
			PATATA_BUILD_SYSTEM, " ", PATATA_BUILD_SYSTEM_VERSION);

	fast_io::io::println(PATATA_TERM_BOLD,
			"  Build Type : ",
			PATATA_TERM_RESET,
			PATATA_BUILD_TYPE);

	fast_io::io::println(PATATA_TERM_BOLD,
			"  Operating System : ",
			PATATA_TERM_RESET,
			PATATA_OS);

	fast_io::io::println(PATATA_TERM_BOLD,
			"  CPU Architecture Type : ",
			PATATA_TERM_RESET,
			PATATA_ARCH);

	#if defined(PATATA_FAST_IO_GIT_COMMIT_HASH_SHORT)
		fast_io::io::println(PATATA_TERM_BOLD,
			"  Fast IO Commit Hash Short : ",
			PATATA_TERM_RESET,
			PATATA_FAST_IO_GIT_COMMIT_HASH_SHORT);
	#endif

	SDL_version sdlversion;
	SDL_VERSION(&sdlversion);

	fast_io::io::println(PATATA_TERM_BOLD,
		"  SDL Version : ",
		PATATA_TERM_RESET,
		sdlversion.major, ".", sdlversion.minor, ".", sdlversion.patch);

	#if defined(PATATA_YAML_CPP_VERSION)
	if (strcmp(PATATA_YAML_CPP_VERSION, "undefined") != 0)
		fast_io::io::println(PATATA_TERM_BOLD, "  Yaml-Cpp Version : ", PATATA_TERM_RESET, PATATA_YAML_CPP_VERSION);
	#endif

	fast_io::io::println("");
}

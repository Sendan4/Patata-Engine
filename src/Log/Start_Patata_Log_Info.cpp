// OS
#if __linux__ && !__ANDROID__
	#define PATATA_OS "Linux"
#elif _WIN64 || _WIN32
	#define PATATA_OS "Windows"
#endif

// Compiler
#if __GNUC__
	#if __MINGW64__
		#define PATATA_COMPILER "MinGW"
	#else
		#define PATATA_COMPILER "GCC"
	#endif
#elif __clang__
	#define PATATA_COMPILER "Clang"
#elif _MSC_VER <= 1929
	#define PATATA_COMPILER "Old Microsoft Visual C++ (MSVC)"
#elif _MSC_VER >= 1930
	#define PATATA_COMPILER "Microsoft Visual C++ (MSVC)"
#endif

#include <fast_io.h>

// Patata Engine
#include "Log.hpp"
#include "TerminalColors.hpp"

void Patata::Log::StartPatataLogInfo(void) {
	fast_io::io::println(LightSalmon3, Bold, PATATA_ENGINE_NAME, Reset, Bold, " INFO", Reset);
	
	#if defined(PATATA_GIT_BRANCH)
	fast_io::io::println(Bold, "  Git Branch : ", Reset, PATATA_GIT_BRANCH);
	#endif

	#if defined(PATATA_GIT_HASH_LONG)
		fast_io::io::print(Bold, "  Git Commit Hash Long", Reset, " : ", Reset, PATATA_GIT_HASH_LONG);

		#if defined(PATATA_GIT_WORK_DIR_IS_CLEAN)
			if (PATATA_GIT_WORK_DIR_IS_CLEAN == "Clean")
				fast_io::io::print(Chartreuse1);
			else
				fast_io::io::print(BLightGoldenRod1);
			fast_io::io::print(" ", PATATA_GIT_WORK_DIR_IS_CLEAN);
		#endif

		#if defined(PATATA_GIT_WORK_DIR_IS_STAGED)
			fast_io::io::print(Reset, " | ");

			if (PATATA_GIT_WORK_DIR_IS_STAGED == "Staged")
				fast_io::io::print(Chartreuse1);
			else
				fast_io::io::print(BLightGoldenRod1);
	
			fast_io::io::print(PATATA_GIT_WORK_DIR_IS_STAGED);
		#endif

	fast_io::io::println(Reset);
	#endif

	#if defined(PATATA_GIT_HASH_SHORT)
	fast_io::io::print(Bold, "  Git Commit Hash Short", Reset, " : ", PATATA_GIT_HASH_SHORT);

		#if defined(PATATA_GIT_WORK_DIR_IS_CLEAN)
			if (PATATA_GIT_WORK_DIR_IS_CLEAN == "Clean")
				fast_io::io::print(Chartreuse1);
			else
				fast_io::io::print(BLightGoldenRod1);
			fast_io::io::print(" ", PATATA_GIT_WORK_DIR_IS_CLEAN);
		#endif

		#if defined(PATATA_GIT_WORK_DIR_IS_STAGED)
			fast_io::io::print(Reset, " | ");

			if (PATATA_GIT_WORK_DIR_IS_STAGED == "Staged")
				fast_io::io::print(Chartreuse1);
			else
				fast_io::io::print(BLightGoldenRod1);
	
			fast_io::io::print(PATATA_GIT_WORK_DIR_IS_STAGED);
		#endif

	fast_io::io::println(Reset);
	#endif

	#if defined(PATATA_GIT_COMMIT_AUTHOR_AND_TIME)
	fast_io::io::println(Bold, "  Git Commit Author And Date : ", Reset, PATATA_GIT_COMMIT_AUTHOR_AND_TIME);
	#endif

	fast_io::io::println(Bold, "  Build Date : ", Reset, __DATE__, " ", __TIME__);
	fast_io::io::println(Bold, "  Version : ", Reset, PATATA_ENGINE_VERSION);
	fast_io::io::println(Bold, "  Compiler : ", Dim, CGREY66, "[", PATATA_COMPILER_PROGRAM, "] ", Reset, PATATA_COMPILER, " ", PATATA_COMPILER_VERSION);
	fast_io::io::println(Bold, "  Build System : ", Dim, CGREY66, "[" , PATATA_BUILD_SYSTEM_GENERATOR, " ", PATATA_BUILD_SYSTEM_GENERATOR_VERSION, "] ", Reset, PATATA_BUILD_SYSTEM, " ", PATATA_BUILD_SYSTEM_VERSION);
	fast_io::io::println(Bold, "  Build Type : ", Reset, PATATA_BUILD_TYPE);
	fast_io::io::println(Bold, "  Operating System : ", Reset, PATATA_OS);
	fast_io::io::println(Bold, "  CPU Architecture Type : ", Reset, PATATA_ARCH);

	#if defined(PATATA_FAST_IO_GIT_COMMIT_HASH_SHORT)
		fast_io::io::println(Bold, "  Fast IO Commit Hash Short : ", Reset, PATATA_FAST_IO_GIT_COMMIT_HASH_SHORT);
	#endif

	SDL_version sdlversion;
	SDL_VERSION(&sdlversion);

	fast_io::io::println(Bold, "  SDL Version : ", Reset, sdlversion.major, ".", sdlversion.minor, ".", sdlversion.patch);

	#if defined(PATATA_YAML_CPP_VERSION)
		fast_io::io::println(Bold , "  Yaml-Cpp Version : ", Reset, PATATA_YAML_CPP_VERSION);
	#endif
	fast_io::io::println("");
}

#include <fast_io.h>
#include <windows.h>

// Patata Engine
#include "PatataEngine/Log.hpp"

void Patata::Log::StartPatataLogInfo(void) {
	HANDLE Terminal = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(Terminal, 14);
	fast_io::io::println(fast_io::out(), PATATA_ENGINE_NAME, " :");
	SetConsoleTextAttribute(Terminal, 7);
	
	#if defined(PATATA_GIT_BRANCH)
	fast_io::io::println(fast_io::out(), "    GIT Branch              : ", PATATA_GIT_BRANCH);
	#endif

	#if defined(PATATA_GIT_HASH_LONG)
	fast_io::io::println(fast_io::out(), "    GIT Commit Hash Long    : ", PATATA_GIT_HASH_LONG);
	#endif

	#if defined(PATATA_GIT_HASH_SHORT)
	fast_io::io::println(fast_io::out(), "    GIT Commit Hash Short   : ", PATATA_GIT_HASH_SHORT);
	#endif

	fast_io::io::println(fast_io::out(), "    Version                 : ", PATATA_VERSION);
	fast_io::io::println(fast_io::out(), "    Compiler                : ", PATATA_COMPILER, PATATA_COMPILER_PROGRAM);
	fast_io::io::println(fast_io::out(), "    Build System            : ", PATATA_BUILD_SYSTEM);
	fast_io::io::println(fast_io::out(), "    Build Type              : ", PATATA_BUILD_TYPE);
	fast_io::io::println(fast_io::out(), "    Operating System        : ", PATATA_OS);
}

#include <fast_io.h>

// Patata Engine
#include "PatataEngine/Log.hpp"
#include "PatataEngine/TerminalColors.hpp"

void Patata::Log::StartPatataLogInfo(void) {
	fast_io::io::println(BLightGoldenRod1, Bold, PATATA_ENGINE_NAME, " :", Reset);
	
	#if defined(PATATA_GIT_BRANCH)
	fast_io::io::println(Bold, "    GIT Branch              : ", Reset, PATATA_GIT_BRANCH);
	#endif

	#if defined(PATATA_GIT_HASH_LONG)
	fast_io::io::println(Bold, "    GIT Commit Hash Long    : ", Reset, PATATA_GIT_HASH_LONG);
	#endif

	#if defined(PATATA_GIT_HASH_SHORT)
	fast_io::io::println(Bold, "    GIT Commit Hash Short   : ", Reset, PATATA_GIT_HASH_SHORT);
	#endif

	fast_io::io::println(Bold, "    Version                 : ", Reset, PATATA_VERSION);
	fast_io::io::println(Bold, "    Compiler                : ", Reset, PATATA_COMPILER, PATATA_COMPILER_PROGRAM);
	fast_io::io::println(Bold, "    Build System            : ", Reset, PATATA_BUILD_SYSTEM);
	fast_io::io::println(Bold, "    Build Type              : ", Reset, PATATA_BUILD_TYPE);
	fast_io::io::println(Bold, "    Operating System        : ", Reset, PATATA_OS);}

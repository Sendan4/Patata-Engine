#include <fast_io.h>

// Patata Engine
#include "PatataEngine/Log.hpp"
#include "PatataEngine/TerminalColors.hpp"

void Patata::Log::StartPatataLogInfo(void) {
	fast_io::io::println(BLightGoldenRod1, Bold, PATATA_ENGINE_NAME, " :", Reset);
	
	#if defined(PATATA_GIT_BRANCH)
	fast_io::io::println("    GIT Branch              : ", PATATA_GIT_BRANCH);
	#endif

	#if defined(PATATA_GIT_HASH_LONG)
	fast_io::io::println("    GIT Commit Hash Long    : ", PATATA_GIT_HASH_LONG);
	#endif

	#if defined(PATATA_GIT_HASH_SHORT)
	fast_io::io::println("    GIT Commit Hash Short   : ", PATATA_GIT_HASH_SHORT);
	#endif

	fast_io::io::println("    Version                 : ", PATATA_VERSION);
	fast_io::io::println("    Compiler                : ", PATATA_COMPILER, PATATA_COMPILER_PROGRAM);
	fast_io::io::println("    Build System            : ", PATATA_BUILD_SYSTEM);
	fast_io::io::println("    Build Type              : ", PATATA_BUILD_TYPE);
	fast_io::io::println("    Operating System        : ", PATATA_OS);}

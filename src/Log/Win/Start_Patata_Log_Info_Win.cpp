#include <iostream>
#include <iomanip>
#include <ios>

#include <windows.h>

// Patata Engine
#include "PatataEngine/Log.hpp"

void Patata::Log::StartPatataLogInfo(void) {
	HANDLE Terminal = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(Terminal, 14);
	std::cout << ENGINE_NAME << std::setw(3) << ":\n";
	SetConsoleTextAttribute(Terminal, 7);
	
	#if defined(GIT_BRANCH)
	std::cout << std::setw(4) << ' ' << "Git Branch" << std::setw(16) << ": " << GIT_BRANCH << "\n";
	#endif

	#if defined(GIT_HASH_LONG)
	std::cout << std::setw(4) << ' ' << "Git Long Hash" << std::setw(13) << ": " << GIT_HASH_LONG << "\n";
	#endif

	#if defined(GIT_HASH_SHORT)
	std::cout << std::setw(4) << ' ' << "Git Short Hash" << std::setw(12) << ": " << GIT_HASH_SHORT << "\n";
	#endif

	std::cout << std::setw(4) << ' ' << "Version" << std::setw(19) << ": " << PATATAVERSION << "\n";
	std::cout << std::setw(4) << ' ' << "Compiler" << std::setw(18) << ": " << COMPILER << "\n";
	std::cout << std::setw(4) << ' ' << "Build System" << std::setw(14) << ": " << BUILDSYS << "\n";
	std::cout << std::setw(4) << ' ' << "Build Type" << std::setw(16) << ": " << BUILD_TYPE << "\n";
	std::cout << std::setw(4) << ' ' << "Operating System" << std::setw(10) << ": " << OS << "\n";
}

#include <iostream>
#include <iomanip>
#include <ios>

// Patata Engine
#include "Patata_Engine/Log.hpp"
#include "EngineInfo.hpp"
#include "Patata_Engine/Terminal_Colors.hpp"

void Patata::Log::StartPatataLogInfo(void) {
	std::cout << Bold << BLightGoldenRod1 << "Patata Engine" << std::setw(3) << ":\n" << Reset;

	std::cout << Bold << std::setw(4) << ' ' << "GIT Branch" << std::setw(16) << ": " << Reset << GIT_BRANCH << "\n";
	std::cout << Bold << std::setw(4) << ' ' << "GIT Long Hash" << std::setw(13) << ": " << Reset << GIT_HASH_LONG << "\n";
	std::cout << Bold << std::setw(4) << ' ' << "GIT Short Hash" << std::setw(12) << ": " << Reset << GIT_HASH_SHORT << "\n";

	std::cout << Bold << std::setw(4) << ' ' << "Version" << std::setw(19) << ": " << Reset << PATATAVERSION << "\n";
	std::cout << Bold << std::setw(4) << ' ' << "Compiler" << std::setw(18) << ": " << Reset << COMPILER << "\n";
	std::cout << Bold << std::setw(4) << ' ' << "Build System" << std::setw(14) << ": " << Reset << BUILDSYS << "\n";
	std::cout << Bold << std::setw(4) << ' ' << "Build Type" << std::setw(16) << ": " << Reset << BUILD_TYPE << "\n";
	std::cout << Bold << std::setw(4) << ' ' << "Operating System" << std::setw(10) << ": " << Reset << OS << "\n";
}

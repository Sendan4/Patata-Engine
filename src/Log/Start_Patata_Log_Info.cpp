#include <iostream>

// Patata Engine
#include "Core/Log.hpp"
#include "EngineInfo.hpp"
#include "Core/terminal_colors.hpp"

// OS
#if __linux__ && !__ANDROID__
	#define OS "Linux"
#elif _WIN64 || _WIN32
	#define OS "Windows"
#endif

// Compiler
#if __GNUC__
	#if __MINGW64__
		#define COMPILER "MinGW-w64"
	#else
		#define COMPILER "GCC"
	#endif
#elif __clang__
	#define COMPILER "Clang"
// MSVC aun no esta probado
#elif _MSC_VER <= 1929
	#define COMPILER "Older Visual Studio (MSVC)"
#elif _MSC_VER >= 1930
	#define COMPILER "Visual Studio (MSVC)"
#endif

void Patata::Log::StartPatataLogInfo(void) {
	std::cout << Bold << BLightGoldenRod1 << "Patata Engine:\n" << Reset;
	std::cout << Bold << "  Version:\t" << Reset << PATATAVERSION << "\n";
	std::cout << Bold << "  Branch:\t" << Reset << GIT_BRANCH << "\n";
	std::cout << Bold << "  Git Hash:\t" << Reset << GIT_HASH_LONG << "  (Long)\n";
	std::cout << Bold << "  Git Hash:\t" << Reset << GIT_HASH_SHORT << "  (Short)\n";
	std::cout << Bold << "  Compiler:\t" << Reset << COMPILER << "\n";
	std::cout << Bold << "  BuildSys:\t" << Reset << BUILDSYS << "\n";
	std::cout << Bold << "  BuildType:\t" << Reset << BUILD_TYPE << "\n";
	std::cout << Bold << "  OS:\t\t" << Reset << OS << "\n";

	std::cout << "\n";
}

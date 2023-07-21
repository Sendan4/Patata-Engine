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
		#define Compiler "MinGW-w64"
	#else
		#define Compiler "GCC"
	#endif
#elif __clang__
	#define Compiler "Clang"
// MSVC aun no esta probado
#elif _MSC_VER <= 1929
	#define Compiler "Older Visual Studio (MSVC)"
#elif _MSC_VER >= 1930
	#define Compiler "Visual Studio (MSVC)"
#endif

void Patata::Log::StartPatataLogInfo(void) {
	std::cout << Bold << BLightGoldenRod1 << "Patata Engine:\n" << Reset;
	std::cout << Bold << "  Version:\t" << Reset << PatataVersion << "\n";
	std::cout << Bold << "  Branch:\t" << Reset << GIT_BRANCH << "\n";
	std::cout << Bold << "  Compiler:\t" << Reset << Compiler << "\n";
	#ifdef BuildSys
		std::cout << Bold << "  BuildSys:\t" << Reset << BuildSys << "\n";
	#endif
	std::cout << Bold << "  OS:   \t" << Reset << OS << "\n";

	std::cout << "\n";
}

#include <iostream>

// Patata Engine
#include "Log.hpp"

void Patata::Log::StartMapache(void) {
	#if !(_WIN64)
		std::cout << "🦝 🥔\n";
	#else
		std::cout << "Tanuki\n";
	#endif
}

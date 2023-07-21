#include <iostream>

// Patata Engine
#include "Core/Log.hpp"

void Patata::Log::StartMapache(void) {
	#if !(_WIN64)
		std::cout << "🦝 🥔\n";
	#endif
}

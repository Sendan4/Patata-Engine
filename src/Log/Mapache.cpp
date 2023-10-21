#include <fast_io.h>

// Patata Engine
#include "PatataEngine/Log.hpp"

void Patata::Log::StartMapache(void) {
	#if !(_WIN64)
		fast_io::io::println("🦝 🥔");
	#else
		fast_io::io::println(fast_io::out(), "Tanuki");
	#endif
}

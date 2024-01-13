#if defined(__GNUC__) || defined(__MINGW64__) && !defined(__clang__)
#include <cxxabi.h>
#endif

#include <fast_io.h>

// Patata Engine
#include "Log.hpp"
#include "TerminalColors.hpp"

void Patata::Log::VulkanList(const char *List[], const size_t & ListSize, const bool & FOUND_EXTENSIONS, const std::string & MESSAGE) {
	if (FOUND_EXTENSIONS) {
		fast_io::io::println(PATATA_TERM_BOLD,
			PATATA_TERM_DIM,
			PATATA_TERM_COLOR_GRAY0,
			#if defined(__GNUC__) || defined(__MINGW64__) && !defined(__clang__)
			"[", std::string_view{ abi::__cxa_demangle(typeid(*List).name(), nullptr, nullptr, nullptr) }, "] ",
			#else
			"[", std::string_view{ typeid(*List).name() }, "] ",
			#endif
			PATATA_TERM_RESET,
			PATATA_TERM_BOLD,
			MESSAGE, " : ",
			PATATA_TERM_RESET,
			ListSize + 1);

		for (unsigned int i = 0; i <= ListSize; i++) {
			if (List[i] != nullptr)
				fast_io::io::println("  ", PATATA_TERM_DIM, std::string_view{ List[i] }, PATATA_TERM_RESET);
			else break;
		}
		fast_io::io::println("");
	}
	else ErrorMessage(SDL_GetError());
}

void Patata::Log::VulkanCheck(const std::string & Message, const vk::Result & Result) {
	fast_io::io::print(PATATA_TERM_DIM, 
		PATATA_TERM_COLOR_GRAY0,
		#if defined(__GNUC__) || defined(__MINGW64__) && !defined(__clang__)
		"[", std::string_view{ abi::__cxa_demangle(typeid(Result).name(), nullptr, nullptr, nullptr) }, "] ",
		#else
		"[", std::string_view{ typeid(Result).name() }, "] ",
		#endif
		PATATA_TERM_RESET,
		PATATA_TERM_BOLD,
		Message, " : ",
		PATATA_TERM_RESET);

	if (Result != vk::Result::eSuccess)
		fast_io::io::print(PATATA_TERM_COLOR_YELLOW);
	else
		fast_io::io::print(PATATA_TERM_COLOR_GREEN);

	fast_io::io::println(vk::to_string(Result), PATATA_TERM_RESET);
}

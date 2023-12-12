#include <cstddef>
#if defined(__GNUC__) || defined(__MINGW64__)
#include <cxxabi.h>
#endif

#include <fast_io.h>
#include <iterator>

// Patata Engine
#include "Log.hpp"
#include "TerminalColors.hpp"

void Patata::Log::VulkanList(const char *List[], const unsigned int & ListSize, bool FOUND_EXTENSIONS, const std::string & MESSAGE) {
	if (FOUND_EXTENSIONS) {
		fast_io::io::println(Reset, Dim, CGREY66, "[", std::string_view{ abi::__cxa_demangle(typeid(*List).name(), nullptr, nullptr, nullptr) }, "] ", Reset, Bold, MESSAGE, Reset, " : ", ListSize + 1);
		for (unsigned int i = 0; i <= ListSize; i++) {
			if (List[i] != nullptr)
				fast_io::io::println("  ", Dim, std::string_view{ List[i] }, Reset);
			else break;
		}
		fast_io::io::println("");
	}
	else ErrorMessage(SDL_GetError());
}

void Patata::Log::VulkanCheck(const std::string & Message, const vk::Result & Result) {
	if (Result != vk::Result::eSuccess) {
		fast_io::io::println(Dim, CGREY66, "[", std::string_view{ abi::__cxa_demangle(typeid(Result).name(), nullptr, nullptr, nullptr) }, "] ", Reset, Bold, Message, " : ", Reset, BLightGoldenRod1, vk::to_string(Result), Reset);
		return;
	}
	else {
		fast_io::io::println(Dim, CGREY66, "[", std::string_view{ abi::__cxa_demangle(typeid(Result).name(), nullptr, nullptr, nullptr) }, "] ", Reset, Bold, Message, " : ", Reset, Chartreuse1, vk::to_string(Result), Reset);
		return;
	}
}

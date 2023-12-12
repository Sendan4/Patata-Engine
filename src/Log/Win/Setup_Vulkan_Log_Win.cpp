#include <cstddef>
#if defined(__GNUC__) || defined(__MINGW64__)
#include <cxxabi.h>
#endif

#include <fast_io.h>
#include <iterator>
#include <Windows.h>

// Patata Engine
#include "Log.hpp"

void Patata::Log::VulkanList(const char* List[], const unsigned int& ListSize, bool FOUND_EXTENSIONS, const std::string& MESSAGE) {
	if (FOUND_EXTENSIONS) {
		HANDLE Terminal = GetStdHandle(STD_OUTPUT_HANDLE);

		SetConsoleTextAttribute(Terminal, FOREGROUND_INTENSITY);

		#if defined(__GNUC__) || defined(__MINGW64__)
			fast_io::io::print(fast_io::out(), "[", std::string_view{ abi::__cxa_demangle(typeid(*List).name(), nullptr, nullptr, nullptr) }, "] ");
		#else
			fast_io::io::print(fast_io::out(), "[", std::string_view{ typeid(*List).name() }, "] ");
		#endif

		SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
		fast_io::io::print(fast_io::out(), MESSAGE, " : ");
		SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		fast_io::io::println(fast_io::out(), ListSize + 1);

		for (unsigned int i = 0; i <= ListSize; i++) {
			if (List[i] != nullptr)
				fast_io::io::println(fast_io::out(), "  ", std::string_view{ List[i] });
			else break;
		}
		fast_io::io::println(fast_io::out());
	}
	else ErrorMessage(SDL_GetError());
}

void Patata::Log::VulkanCheck(const std::string& Message, const vk::Result& Result) {
	HANDLE Terminal = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(Terminal, FOREGROUND_INTENSITY);
	#if defined(__GNUC__) || defined(__MINGW64__)
		fast_io::io::print(fast_io::out(), "[", std::string_view{ abi::__cxa_demangle(typeid(Result).name(), nullptr, nullptr, nullptr) }, "] ");
	#else
		fast_io::io::print(fast_io::out(), "[", std::string_view{ typeid(Result).name() }, "] ");
	#endif

	SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	fast_io::io::print(fast_io::out(), Message, " : ");

	if (Result != vk::Result::eSuccess)
		SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	else
		SetConsoleTextAttribute(Terminal, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	fast_io::io::println(fast_io::out(), vk::to_string(Result));
	SetConsoleTextAttribute(Terminal, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

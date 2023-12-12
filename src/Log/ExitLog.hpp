namespace Patata {
	namespace Log {
		template <typename pointer>
		void DeleteAndLogPtr(const std::string & Message, pointer *& ptr) {
			if (ptr != nullptr) {
				delete ptr;
				ptr = nullptr;

				#if defined(_WIN64)
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);

					#if defined(__GNUC__) || defined(__MINGW64__)
						fast_io::io::print(fast_io::out(), "[", std::string_view{ abi::__cxa_demangle(typeid(*ptr).name(), nullptr, nullptr, nullptr) }, "] ");
					#else
						fast_io::io::print(fast_io::out(), "[", std::string_view{ typeid(*ptr).name() }, "] ");
					#endif

					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);

					fast_io::io::print(fast_io::out(), Message, " Pointer Removed : ");
				#else
					#if defined(__GNUC__) || defined(__MINGW64__)
						fast_io::io::print(Dim, CGREY66, "[", std::string_view{ abi::__cxa_demangle(typeid(*ptr).name(), nullptr, nullptr, nullptr) }, "] ", Reset);
					#else
						fast_io::io::print(Dim, CGREY66, "[", std::string_view{ typeid(*ptr).name() }, "] ");
					#endif

					fast_io::io::print(Message, " Pointer Removed : ");
				#endif

				if (ptr == nullptr) {
					#if defined(_WIN64)
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
						fast_io::io::println(fast_io::out(), "Success");
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
					#else
						fast_io::io::println(Chartreuse1, "Success", Reset);
					#endif
				}
				else {
					#if defined(_WIN64)
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		fast_io::io::println(fast_io::out(), "Fail");
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
					#else
						fast_io::io::println(BLightGoldenRod1, "Fail", Reset);
					#endif
				}
			}
			else {
				#if defined(_WIN64)
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
					#if defined(__GNUC__) || defined(__MINGW64__)
						fast_io::io::print(fast_io::out(), "[", std::string_view{ abi::__cxa_demangle(typeid(ptr).name(), nullptr, nullptr, nullptr) }, "] ");
					#else
						fast_io::io::print(fast_io::out(), "[", std::string_view{ typeid(ptr).name() }, "] ");
					#endif

					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
					fast_io::io::println(fast_io::out(), Message, " Already Eliminated Or Null");
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
				#else
				fast_io::io::println(Dim, CGREY66, "[", std::string_view{ abi::__cxa_demangle(typeid(ptr).name(), nullptr, nullptr, nullptr) }, "] ", Reset, Bold, Message, " Already Eliminated Or Null", Reset);
				#endif
			}
		}

		template <typename pointer>
		void DeleteAndLogArrPtr(const std::string & Message, pointer *& ptr) {
			if (ptr != nullptr) {
				delete [] ptr;
				ptr = nullptr;

				#if defined(_WIN64)
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);

					#if defined(__GNUC__) || defined(__MINGW64__)
						fast_io::io::print(fast_io::out(), "[", std::string_view{ abi::__cxa_demangle(typeid(*ptr).name(), nullptr, nullptr, nullptr) }, "] ");
					#else
						fast_io::io::print(fast_io::out(), "[", std::string_view{ typeid(*ptr).name() }, "] ");
					#endif

					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);

					fast_io::io::print(fast_io::out(), Message, " Array Pointer Removed : ");
				#else
					#if defined(__GNUC__) || defined(__MINGW64__)
						fast_io::io::print(Dim, CGREY66, "[", std::string_view{ abi::__cxa_demangle(typeid(*ptr).name(), nullptr, nullptr, nullptr) }, "] ", Reset);
					#else
						fast_io::io::print(Dim, CGREY66, "[", std::string_view{ typeid(*ptr).name() }, "] ");
					#endif

					fast_io::io::print(Message, " Array Pointer Removed : ");
				#endif

				if (ptr == nullptr) {
					#if defined(_WIN64)
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
						fast_io::io::println(fast_io::out(), "Success");
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
					#else
						fast_io::io::println(Chartreuse1, "Success", Reset);
					#endif
				}
				else {
					#if defined(_WIN64)
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
						fast_io::io::println(fast_io::out(), "Fail");
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
					#else
						fast_io::io::println(BLightGoldenRod1, "Fail", Reset);
					#endif
				}
			}
			else {
				#if defined(_WIN64)
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
					#if defined(__GNUC__) || defined(__MINGW64__)
						fast_io::io::print(fast_io::out(), "[", std::string_view{ abi::__cxa_demangle(typeid(ptr).name(), nullptr, nullptr, nullptr) }, "] ");
					#else
						fast_io::io::print(fast_io::out(), "[", std::string_view{ typeid(ptr).name() }, "] ");
					#endif

					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
					fast_io::io::println(fast_io::out(), Message, " Already Eliminated Or Null");
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
				#else
				fast_io::io::println(Dim, CGREY66, "[", std::string_view{ abi::__cxa_demangle(typeid(ptr).name(), nullptr, nullptr, nullptr) }, "] ", Reset, Bold, Message, " Already Eliminated Or Null", Reset);
				#endif
			}
		}
	}
}

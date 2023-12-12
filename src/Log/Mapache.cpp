#include <cstdlib>
#include <ctime>

#include <fast_io.h>
#if defined(_WIN64)
#include <windows.h>
#endif

// Patata Engine
#include "Log.hpp"

void Patata::Log::StartMapache(void) {
	#if defined(_WIN64)
		UINT defaultOutputCP = GetConsoleOutputCP();
		SetConsoleOutputCP(CP_UTF8);
	#endif

	srand(time(nullptr));

	switch (rand() % 12) {
		case 1: case 2:
			#if !(_WIN64)
				fast_io::io::println("🦝 🥔");
			#else
				fast_io::io::println(fast_io::out(), "Mapache");
			#endif
			break;

		case 3: case 4: case 5:
			#if !(_WIN64)
				fast_io::io::println("🦝 UwU");
			#else
				fast_io::io::println(fast_io::out(), "UwU");
			#endif
			break;

		case 6:
			#if !(_WIN64)
				fast_io::io::println("🦝 ¿Que Control Estas Usando?");
			#else
				fast_io::io::println(fast_io::out(), "¿Que Control Estas Usando?");
			#endif
			break;

		case 7: case 8: case 9:
			#if !(_WIN64)
				fast_io::io::println("🦝 ¿Sabes?, a [Nombre de la mascota] le encantan las papas");
			#else
				fast_io::io::println(fast_io::out(), "¿Sabes?, a [Nombre la mascota] le encantan las papas");
			#endif
			break;

		#if defined(__linux__)
		case 10:
			fast_io::io::println("🦝 ☺️ A mi tambien me gustan los sistemas operativos abiertos por diseño");
			break;
		#elif !defined(__linux__) && !defined(_WIN64) && !defined(_WIN32)
		case 10:
			fast_io::io::println("🦝 Espera... ¿!Estas ejecutando el motor en un UNIX-LIKE!? 🤨");
			break;
		#endif
	}
	#if defined(_WIN64)
		SetConsoleOutputCP(defaultOutputCP);
	#endif
}

// Patata Engine
#include "Patata_Engine/Patata_Engine.hpp"

int main(int argv, char** args) {
	static_cast<void>(argv);
	static_cast<void>(args);

	Patata::PatataEngine Patata(
			"", // Window Title
			1280, // Window Width
			720); // Window Height

	Patata.MainLoop();
	return 0;
}

// Patata Engine
#include "Core/Patata_Engine.hpp"
#include <iostream>

int main(int argc, char **argv) {
	Patata::PatataEngine Patata(
			"", // Window Title
			1280, // Window Width
			720, // Window Height
			Patata::api::Opengl); // API

	Patata.MainLoop();
	return 0;
}

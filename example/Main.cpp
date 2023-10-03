// Patata Engine
#include <Patata_Engine.hpp>

int main(int argc, char* argv[]) {


	Patata::PatataEngine Patata(
			"", // Window Title (Subtituido por GAME_NAME si esta definido y vacio como en este caso)
			1280, // Window Width
			720); // Window Height

	while (true) {
		if (!Patata.Input()) break;

		Patata.Render();
	}

	return 0;
}

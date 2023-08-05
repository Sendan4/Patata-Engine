//#include <glad/gl.h>

// Patata Engine
#include "Core/Patata_Engine.hpp"

void Patata::PatataEngine::MainLoop(void) {
	SDL_Event Window_Event;

	do {
		SDL_PollEvent(&Window_Event);
		if (Window_Event.type == SDL_QUIT)
			break;

		//glClearColor(0.113f, 0.578f, 0.810f, 0.0f);
		//glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		//GLSwapMainLoopWrapper();
	} while (true);
}

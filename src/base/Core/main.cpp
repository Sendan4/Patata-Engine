#include "init.hpp"
#include "window.hpp"
#include "Events.hpp"
#include "Opengl_context.hpp"
#include "init_graphics_switcher.hpp"
#include <SDL.h>
#include <glad/glad.h>
#include <iostream>

int main(int argc, char **argv) {
    initSDL();

	sdl_opengl_atributos();

	Game::Window MainWindow;
	MainWindow.start();

	start_opengl(MainWindow.window_get(), MainWindow.glcontext_get());

	do {
		SDL_PollEvent(&Window_Event);
		if (Window_Event.type == SDL_QUIT)
			break;

		glClearColor(1.0f, 0.2f, 0.2f, 0.0f);
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		SDL_GL_SwapWindow(MainWindow.window_get());
	} while (true);

	MainWindow.finish();
	SDL_Quit();
    return 0;
}
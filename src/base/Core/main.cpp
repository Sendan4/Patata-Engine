/*
Vulkan 0.980f, 0.285f, 0.235f
OpenGL 0.113f, 0.578f, 0.810f
*/

#include "begin.hpp"
#include "finish.hpp"

#include "window.hpp"
#include "Events.hpp"

#include "API_Graphics_Switch.hpp"
#include "Vulkan.hpp"
#include "Opengl_context.hpp"

//#include <glad/glad.h>

int main(int argc, char **argv) {
	std::cout << "😺 🥔" << std::endl;
	Game::begin();
	
	Game::Window MainWindow;
	MainWindow.Start("Patata Engine", 1280 ,720);

	// Vulkan
	Graphics::VulkanRenderer Vulkan(MainWindow.Window_get());

	do {
		SDL_PollEvent(&Window_Event);
		if (Window_Event.type == SDL_QUIT)
			break;

		//glClearColor(0.113f, 0.578f, 0.810f, 0.0f);
		//glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		//SDL_GL_SwapWindow(MainWindow.window_get());
	} while (true);

	// Finish
	MainWindow.Finish();
	Game::finish();
	return 0;
}

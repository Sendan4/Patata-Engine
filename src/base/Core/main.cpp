/*
Vulkan 0.980f, 0.285f, 0.235f
OpenGL 0.113f, 0.578f, 0.810f
*/

//#include <glad/glad.h>
#include "sdl.hpp"

#include "window.hpp"
#include "Events.hpp"

#include "API_Graphics_Switch.hpp"
#include "Vulkan.hpp"
#include "Opengl_context.hpp"


int main(int argc, char **argv) {
	Game::SDL sdl;

	std::cout << "😺 🥔" << std::endl;

	//Graphics::sdl_opengl_atributos();
	
	Game::Window MainWindow("Patata Engine", 1280 ,720, GraphicsApi::VULKAN);

	//SDL_GLContext Contexto = NULL;
	Graphics::VulkanRenderer Vulkan(MainWindow.Window_get());

	MainWindow.WindowRendererStart();
	//Contexto = Graphics::start_opengl(MainWindow.Window_get());

	do {
		SDL_PollEvent(&Window_Event);
		if (Window_Event.type == SDL_QUIT)
			break;

		//glClearColor(0.113f, 0.578f, 0.810f, 0.0f);
		//glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		//SDL_GL_SwapWindow(MainWindow.Window_get());
	} while (true);

	//SDL_GL_DeleteContext(Contexto);
	return 0;
}

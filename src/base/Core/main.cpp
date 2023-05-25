/*
Vulkan 0.980f, 0.285f, 0.235f
OpenGL 0.113f, 0.578f, 0.810f
*/

#include "Core/sdl.hpp"

#include "Core/window.hpp"
#include "Core/Events.hpp"

#include "Graphics/API_Graphics_Switch.hpp"
#include "Graphics/Vulkan.hpp"
#include "Graphics/Opengl_context.hpp"
#include <glad/gl.h>

int main(int argc, char **argv) {
	Game::SDL sdl;
	#if !(_WIN64)
		std::cout << "😺 🥔" << std::endl;
	#endif
	Game::Window MainWindow("", 1280 ,720, GraphicsApi::OPENGL);

	//Graphics::VulkanRenderer Vulkan(MainWindow.Window_get());
	Graphics::sdl_opengl_atributos();
	SDL_GLContext gl = nullptr;
	Graphics::start_opengl(MainWindow.Window_get(), gl);

	do {
		SDL_PollEvent(&Window_Event);
		if (Window_Event.type == SDL_QUIT)
			break;

		glClearColor(0.113f, 0.578f, 0.810f, 0.0f);
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		SDL_GL_SwapWindow(MainWindow.Window_get());
	} while (true);
	return 0;
}

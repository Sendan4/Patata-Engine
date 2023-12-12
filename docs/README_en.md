| [Español](../README.md) | English |
| :--: | :--: |

# <img draggable=false src = "data/assets/icon/patata-debug.webp" width=24 style="image-rendering: pixelated;">Potato Engine

<img draggable=false src = "data/assets/icon/patata_icon.svg" width=60 align=left style="margin:10px 10px;">

<p><b>Potato Engine</b> is a simple and light 2d engine with a focus on video game development.</p>

<p>I'm a newbie in <b>C++</b>, I'm doing this project to learn and have fun developing it, so don't expect to see a professional code.</p>

<p>Another goal is <b>portability</b>, I want it to be able to run on old (not so old) and modern devices.</p>

⚠️ Not ready for use yet

## Ejemplo de su uso
[Programa de Ejemplo](examples/Simple Program/Main.cpp)

```cpp
#include <SDL.h>
#include <PatataEngine/PatataEngine.hpp>

int main(int argc, char ** argv) {
    Patata::Engine Patata;

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) exit(1);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_Window * window = SDL_CreateWindow(
		#if defined(DEBUG)
		"Patata Engine | Debug (Development)",
		#else
		"Patata Engine",
		#endif
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        1280, 720,
        Patata.GetWindowFlags());

	SDL_GLContext * context = nullptr;
 
	Patata.Info->pWindow = window;
	Patata.Info->pOpenGLContext = context;

	Patata.InitRenderer();

	bool run = true;
	while(run) {
		SDL_Event event;
		while(SDL_PollEvent(&event)) {
			// Patata Events
			Patata.HandleEvent(event);
			// Your Events
			if (event.type == SDL_QUIT) {
				run = false;
				break;
			}
		}
		
		// Your Render Functions

		Patata.Render();
	}
	
	if(*Patata.pGraphicsAPI == Patata::GraphicsAPI::OpenGL) {
		SDL_GL_DeleteContext(context);
		delete context;
		context = nullptr;
	}

	SDL_DestroyWindow(window);

	return 0;
}
```

# Available Operating Systems

| Windows | GNU/Linux |
| :-----: | :-----: |
|<b>[x86_64]()</b> | <b>[x86_64]()</b> |

# targets

- [ ] Portability of binary distribution *(Linux distros)*
- [ ] Make the engine portable
- [ ] Example Menu
- [X] Configuration Management
- [ ] Hot set-up
- [ ] Audio Output
- [ ] Vulkan Renderer
- [ ] OpenGL Renderer
- [ ] Create a Mascot
- [ ] Decode, Load and Render images ([AVIF](https://aomediacodec.github.io/av1-avif/))
- [ ] Sequential playback of sprite animations
- [ ] Appropriate Wayland (Linux) Support
- [X] Create a logo or symbol

## TODO
- VkLayerKhronosValidation must be found by Patata if it is compiled with ```USE_EXTERNAL_LIBS```, and it must be in the same directory.
- Re-do the way Patata can load or accept icons for the window

## Third-party libraries used in this project
<ul>
	<li><a href = "http://www.libsdl.org/">SDL2</a></li>
	<li><a href = "https://www.vulkan.org/">Vulkan</a></li>
	<ul>
		(<a href = "https://github.com/KhronosGroup/Vulkan-Headers.git">Vulkan-Headers</a>)
		(<a href = "https://github.com/KhronosGroup/Vulkan-ValidationLayers.git">Vulkan-ValidationLayers</a>)
		(<a href = "https://github.com/KhronosGroup/Vulkan-Loader.git">Vulkan-Loader</a>)
	</ul>
	<li><a href = "https://github.com/cppfastio/fast_io.git">fast_io</a></li>
	<li><a href = "https://github.com/Dav1dde/glad.git">Glad 2</a></li>
	<li><a href = "https://github.com/jbeder/yaml-cpp.git">yaml-cpp</a></li>
    <li><a href = "https://github.com/ocornut/imgui.git">Imgui</a></li>
</ul>

<hr>


### [Access to the documentation](doc/README.md)

<hr>

## Ifficial Mirrors
- [Github](https://github.com/Sendan4/Patata-Engine.git)
- [Codeberg](https://codeberg.org/Sendan/patata-engine.git)

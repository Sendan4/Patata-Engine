#include <SDL.h>
#include <iostream>

void initSDL(void) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
		std::cout << "SDL - SubSistema de video no se ha podido iniciar : " << std::endl << SDL_GetError() << std::endl;
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Problemas al iniciar", "SDL Fallo al iniciar los subsistemas", NULL);
	}
}

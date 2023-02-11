// inicializador
#include "init.hpp"
// Ventana
#include "window.hpp"

int main(int argc, char **argv) {
    initSDL();

	Window window;

	window.createWindowAndRender();

	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Patata Engine", "Este Mensaje Mantiene el programa abierto.", NULL);

	window.deleteWindowAndRender();

	SDL_Quit();
    return 0;
}

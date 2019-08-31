// SDL2 Hello, World!
// This should display a white screen for 2 seconds
// compile with: clang++ main.cpp -o hello_sdl2 -lSDL2
// run with: ./hello_sdl2
#include <SDL.h>
#include <stdio.h>

#include "Game.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

int main(int argc, char* args[]) {

	Game* game = new Game();
	game->initialize();
	game->run();

	delete game;

	return 0;

}
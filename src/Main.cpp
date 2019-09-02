#include <SDL.h>
#include <stdio.h>

#include "Game.h"

int main(int argc, char* args[]) {

	Game* game = new Game();
	game->initialize();
	game->run();

	delete game;

	return 0;

}


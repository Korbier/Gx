#pragma once

#include <stack>

#include <SDL.h>

#include "input/InputBuffer.h"
#include "gamestate/Gamestate.h"

class Gamestate;

class GameStateManager
{
public:

	void push(Gamestate* gstate);
	void replace(Gamestate* gstate);
	void pop();
	void pop(unsigned int count);

	void update(InputBuffer input, Uint32 delta);
	void render();

private:
	std::stack<Gamestate*> gamestates;

};


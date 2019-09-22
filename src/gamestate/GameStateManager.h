#pragma once

#include <stack>
#include "SDL.h"

class Gamestate;
class InputBuffer;

class GameStateManager
{
public:

	void push(Gamestate* gstate);
	void replace(Gamestate* gstate);
	void pop();

	void update(InputBuffer input, Uint32 delta);
	void render();

private:
	std::stack<Gamestate*> gamestates;

};


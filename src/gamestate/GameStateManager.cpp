#include "GameStateManager.h"

#include "gamestate/Gamestate.h"

void GameStateManager::push(Gamestate* gstate)
{
	gstate->initialize();
	this->gamestates.push(gstate);
}

void GameStateManager::pop()
{
	Gamestate* top = this->gamestates.top();
	delete top;

	this->gamestates.pop();
	
}

void GameStateManager::replace(Gamestate* gstate)
{
	this->pop();
	this->push(gstate);
}

void GameStateManager::update(InputBuffer input, Uint32 delta)
{
	this->gamestates.top()->update(input, delta);
}

void GameStateManager::render()
{
	this->gamestates.top()->render();
}

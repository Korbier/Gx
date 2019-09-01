#pragma once

class Game;

class GameHandler
{
public:
	void initialize(Game* game);
	void stop();
private:
	Game* game = nullptr;
};


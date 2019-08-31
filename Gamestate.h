#pragma once
#include "Window.h"

class Gamestate
{
public:
	
	void initialize(Window* window);
	void finalize();

	void input();
	void update();
	void render();

private:
	Window* window = NULL;
};


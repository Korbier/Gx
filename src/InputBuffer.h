#pragma once

#include "SDL.h"
class InputBuffer
{
public:
	void press(SDL_Scancode code);
	void release(SDL_Scancode code);
	SDL_bool isPressed(SDL_Scancode code);
private:
	SDL_bool key[SDL_NUM_SCANCODES];
};


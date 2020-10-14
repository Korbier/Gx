#pragma once

#include <SDL.h>

class InputBuffer
{
public:
	
	void press(SDL_Scancode code, SDL_bool keyrepeat);
	void release(SDL_Scancode code);
	SDL_bool isPressed(SDL_Scancode code);
	SDL_bool isRepeated(SDL_Scancode code);

	void pressMouseLeft();
	void releaseMouseLeft();
	SDL_bool isMouseLeftPressed();

	void updateMouse();
	void mousePosition(SDL_Point* position);

private:

	SDL_bool key[SDL_NUM_SCANCODES];
	SDL_bool repeat[SDL_NUM_SCANCODES];

	SDL_Point mouse;
	SDL_bool mouseLeft;
};


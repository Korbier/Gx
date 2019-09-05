#include "InputBuffer.h"

void InputBuffer::press(SDL_Scancode code)
{
	this->key[code] = SDL_TRUE;
}

void InputBuffer::release(SDL_Scancode code)
{
	this->key[code] = SDL_FALSE;
}

SDL_bool InputBuffer::isPressed(SDL_Scancode code)
{
	return this->key[code];
}

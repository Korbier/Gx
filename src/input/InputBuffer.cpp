#include "InputBuffer.h"

void InputBuffer::press(SDL_Scancode code, SDL_bool keyrepeat)
{
	this->key[code] = SDL_TRUE;
	this->repeat[code] = keyrepeat;
}


void InputBuffer::release(SDL_Scancode code)
{
	this->key[code] = SDL_FALSE;
}

SDL_bool InputBuffer::isPressed(SDL_Scancode code)
{
	return this->key[code];
}

SDL_bool InputBuffer::isRepeated(SDL_Scancode code)
{
	return this->repeat[code];
}

void InputBuffer::pressMouseLeft()
{
	this->mouseLeft = SDL_TRUE;
}

void InputBuffer::releaseMouseLeft()
{
	this->mouseLeft = SDL_FALSE;
}

SDL_bool InputBuffer::isMouseLeftPressed()
{
	return this->mouseLeft;
}

void InputBuffer::updateMouse()
{
	SDL_GetMouseState(&this->mouse.x, &this->mouse.y);
}

void InputBuffer::mousePosition(SDL_Point* position)
{
	position->x = this->mouse.x;
	position->y = this->mouse.y;
}

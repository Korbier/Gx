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

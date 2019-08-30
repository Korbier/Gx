#include "Window.h"

bool Window::initialize(const char* title, int width, int height, bool fullscreen)
{

	Uint32 flag = SDL_WINDOW_SHOWN;
	if (fullscreen) flag |= SDL_WINDOW_FULLSCREEN;

	this->window = SDL_CreateWindow(
		title,
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		width, 
		height,
		flag
	);

	if (this->window == NULL) {
		fprintf(stderr, "could not create window: %s\n", SDL_GetError());
		return false;
	}

	return true;

}

void Window::finalize()
{
	SDL_DestroyWindow( this->window );
}

void Window::show()
{
	SDL_UpdateWindowSurface( this->window );
}


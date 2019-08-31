#include "Window.h"

bool Window::initialize(const char* title, int width, int height, bool fullscreen)
{

	this->fullscreen = fullscreen;

	Uint32 flag = SDL_WINDOW_SHOWN;
	if ( this->isFullscreen() ) flag |= SDL_WINDOW_FULLSCREEN;

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
	else {
		fprintf(stdout, "Window created\n");
	}

	this->renderer = SDL_CreateRenderer(this->window, -1, 0);
	if (this->renderer == NULL) {
		fprintf(stderr, "could not create renderer: %s\n", SDL_GetError());
		return false;
	}
	else {
		fprintf(stdout, "Renderer created\n");
	}

	return true;

}

void Window::finalize()
{
	SDL_DestroyWindow( this->window );
}

void Window::setFullscreen(bool fullscreen)
{
	this->fullscreen = fullscreen;
	SDL_SetWindowFullscreen( this->window, fullscreen ? SDL_WINDOW_FULLSCREEN : 0 );
}

bool Window::isFullscreen()
{
	return this->fullscreen;
}


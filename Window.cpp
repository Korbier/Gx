#include "Window.h"

#define ENABLE_TRACE
#include "Trace.h"

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

	if (this->window == nullptr) {
		ERROR( "could not create window: %s", SDL_GetError() );
		return false;
	}
	else {
		TRACE("Window created");
	}

	this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
	if (this->renderer == nullptr) {
		ERROR("could not create renderer: %s", SDL_GetError());
		return false;
	}
	else {
		SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 255);
		TRACE("Renderer created");
	}

	return true;

}

void Window::finalize()
{	
	SDL_DestroyWindow( this->window );
	SDL_DestroyRenderer( this->renderer );
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

SDL_Window* Window::getWindow()
{
	return this->window;
}

SDL_Renderer* Window::getRenderer()
{
	return this->renderer;
}


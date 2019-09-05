#include "Display.h"

#include <iostream>
#include "boost/log/trivial.hpp"

Display::Display(const char* title, int width, int height, bool fullscreen)
{

	this->fullscreen = fullscreen;
	this->title = title;
	this->width = width;
	this->height = height;


}

void Display::show() {

	Uint32 flag = SDL_WINDOW_SHOWN;
	if (this->isFullscreen()) flag |= SDL_WINDOW_FULLSCREEN;

	this->window = SDL_CreateWindow(
		title,
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		width,
		height,
		flag
	);

	if (this->window == nullptr) {
		BOOST_LOG_TRIVIAL(error) << "could not create window: " << SDL_GetError();
	}
	else {
		BOOST_LOG_TRIVIAL(info) << "Window created";
	}

	this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
	if (this->renderer == nullptr) {
		BOOST_LOG_TRIVIAL(error) << "could not create renderer: " << SDL_GetError();
	}
	else {
		SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, 255);
		BOOST_LOG_TRIVIAL(info) << "Renderer created";
	}
}

Display::~Display()
{
	SDL_DestroyRenderer(this->renderer);
	SDL_DestroyWindow(this->window);
}

void Display::setFullscreen(bool fullscreen)
{
	this->fullscreen = fullscreen;
	SDL_SetWindowFullscreen(this->window, fullscreen ? SDL_WINDOW_FULLSCREEN : 0);
}

bool Display::isFullscreen()
{
	return this->fullscreen;
}

SDL_Window* Display::getWindow()
{
	return this->window;
}

SDL_Renderer* Display::getRenderer()
{
	return this->renderer;
}


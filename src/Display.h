#ifndef WINDOWS_H_
#define WINDOWS_H_

#include <stdio.h>
#include <string>
#include <iostream>

#include <SDL.h>

#include "boost/log/trivial.hpp"

class Display
{

public:

	Display(const char* title, int width, int height, bool fullscreen, bool vsync);
	~Display();

	void show();

	void setFullscreen(bool fullscreen);
	bool isFullscreen();

	void setWindowTitle(std::string title);

	SDL_Window* getWindow();
	SDL_Renderer* getRenderer();

	int getWidth();
	int getHeight();

private:
	SDL_Window*   window     = nullptr;
	SDL_Renderer* renderer   = nullptr;

	bool  fullscreen = false;
	const char* title;
	int   width;
	int   height;
	bool  vsync = true;

};

#endif WINDOWS_H_
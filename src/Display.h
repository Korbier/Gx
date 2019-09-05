#ifndef WINDOWS_H_
#define WINDOWS_H_

#include <SDL.h>
#include <stdio.h>

class Display
{

public:

	Display(const char* title, int width, int height, bool fullscreen);
	~Display();

	void show();

	void setFullscreen(bool fullscreen);
	bool isFullscreen();

	SDL_Window* getWindow();
	SDL_Renderer* getRenderer();

private:
	SDL_Window*   window     = nullptr;
	SDL_Renderer* renderer   = nullptr;

	bool  fullscreen = false;
	const char* title;
	int   width;
	int   height;

};

#endif WINDOWS_H_
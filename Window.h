#ifndef WINDOWS_H_
#define WINDOWS_H_

#include <SDL.h>
#include <stdio.h>

class Window
{

public:

	bool initialize(const char* title, int width, int height, bool fullscreen);
	void finalize();

	void setFullscreen(bool fullscreen);
	bool isFullscreen();

private:
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	bool fullscreen = false;
};

#endif WINDOWS_H_
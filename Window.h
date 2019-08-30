#ifndef WINDOWS_H_
#define WINDOWS_H_

#include <SDL.h>
#include <stdio.h>

class Window
{

public:

	bool initialize(const char* title, int width, int height, bool fullscreen);
	void finalize();

	void show();

private:
	SDL_Window* window = NULL;

};

#endif WINDOWS_H_
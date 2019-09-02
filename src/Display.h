#ifndef WINDOWS_H_
#define WINDOWS_H_

#include <SDL.h>
#include <stdio.h>

class Display
{

public:

	bool initialize(const char* title, int width, int height, bool fullscreen);
	void finalize();

	void setFullscreen(bool fullscreen);
	bool isFullscreen();

	SDL_Window* getWindow();
	SDL_Renderer* getRenderer();

private:
	SDL_Window*   window     = nullptr;
	SDL_Renderer* renderer   = nullptr;
	bool          fullscreen = false;
};

#endif WINDOWS_H_
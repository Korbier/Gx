#pragma once

#include <string>
#include <map>

#include <SDL.h>
#include <SDL_image.h>

#include "boost/log/trivial.hpp"

#include "Display.h"

class Display;

class TextureManager
{
public:
	TextureManager( Display* display );
	~TextureManager();

	SDL_Texture* get(std::string path);

private:
	std::map<std::string, SDL_Texture*> textures;
	Display* display = nullptr;
	SDL_Texture* load(std::string);
};


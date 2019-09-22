#pragma once

#include <string>
#include <map>
#include "SDL.h"

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


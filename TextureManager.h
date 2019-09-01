#pragma once

#include <string>
#include <map>
#include "SDL.h"

class Display;

class TextureManager
{
public:
	void initialize( Display* display );
	void finalize();

	SDL_Texture* get(std::string path);

private:
	std::map<std::string, SDL_Texture*> textures;
	Display* display = nullptr;
	SDL_Texture* load(std::string);
};


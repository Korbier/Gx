#include "TextureManager.h"

#include "SDL_image.h"
#include "Display.h"

#define ENABLE_TRACE
#include "Trace.h"

void TextureManager::initialize( Display* display )
{
	this->display = display;
}

void TextureManager::finalize()
{
	for (std::map<std::string, SDL_Texture*>::iterator ii = this->textures.begin(); ii != this->textures.end(); ++ii)
	{
		TRACE("Destroying texture \"%s\"", &*ii->first.begin());
		SDL_DestroyTexture(ii->second);
	}
}

SDL_Texture* TextureManager::get( std::string path )
{

	SDL_Texture* texture = nullptr;

	auto textureIt = this->textures.find(path);

	if (textureIt == this->textures.end()) {
		TRACE("Loading texture \"%s\" from disk", &*path.begin());
		texture = this->load(path);
		this->textures[path] = texture;
	}
	else {
		TRACE("Loading texture \"%s\" from memory", &*path.begin());
		texture = textureIt->second;
	}

	return texture;

}

SDL_Texture* TextureManager::load( std::string path )
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == nullptr )
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(this->display->getRenderer(), loadedSurface);
		if (newTexture == nullptr)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;

}

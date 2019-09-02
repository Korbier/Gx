#include "TextureManager.h"

#include "SDL_image.h"
#include "boost/log/trivial.hpp"

#include "Display.h"

void TextureManager::initialize( Display* display )
{
	this->display = display;
}

void TextureManager::finalize()
{
	for (std::map<std::string, SDL_Texture*>::iterator ii = this->textures.begin(); ii != this->textures.end(); ++ii)
	{
		BOOST_LOG_TRIVIAL(info) << "Destroying texture \"" << ii->first << "\"";
		SDL_DestroyTexture(ii->second);
	}
}

SDL_Texture* TextureManager::get( std::string path )
{

	SDL_Texture* texture = nullptr;

	auto textureIt = this->textures.find(path);

	if (textureIt == this->textures.end()) {
		BOOST_LOG_TRIVIAL(info) << "Loading texture \"" << path << "\" from disk";
		texture = this->load(path);
		this->textures[path] = texture;
	}
	else {
		BOOST_LOG_TRIVIAL(info) << "Loading texture \"" << path << "\" from memory";
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
		BOOST_LOG_TRIVIAL(error) << "Unable to load image " << path.c_str() << "SDL_image Error: " << IMG_GetError();
	}
	else
	{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(this->display->getRenderer(), loadedSurface);
		if (newTexture == nullptr)
		{
			BOOST_LOG_TRIVIAL(error) << "Unable to create texture from " << path.c_str() << "SDL_image Error: " << SDL_GetError();
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;

}

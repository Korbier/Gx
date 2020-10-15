#include "Text.h"

Text::Text(Display* display, TTF_Font* font)
{
	this->display = display;
	this->font = font;
}

Text::~Text()
{
	if (this->texture != nullptr) {
		SDL_DestroyTexture(this->texture);
	}
}

void Text::setText(std::string text)
{
	this->text = text;
	this->buildTexture();
}

void Text::setColor(SDL_Color color)
{
	this->color = color;
	this->buildTexture();
}

void Text::buildTexture()
{
	
	if (this->texture != nullptr) {
		SDL_DestroyTexture(this->texture);
	}

	SDL_Surface* textSurf = TTF_RenderText_Blended(font, this->text.c_str(), this->color);
	this->width = textSurf->w;
	this->height = textSurf->h;
	this->texture = SDL_CreateTextureFromSurface(this->display->getRenderer(), textSurf);
	SDL_FreeSurface(textSurf);

}

std::string Text::getText()
{
	return this->text;
}

void Text::setPosition(SDL_Point position)
{
	this->position = position;
}

SDL_Point Text::getPosition()
{
	return this->position;
}

void Text::setAngle(float angle)
{
	this->angle = angle;
}

float Text::getAngle()
{
	return this->angle;
}

SDL_Texture* Text::getTexture()
{
	return this->texture;
}


SDL_Color Text::getColor()
{
	return this->color;
}

int Text::getWith()
{
	return this->width;
}

int Text::getHeight()
{
	return this->height;
}

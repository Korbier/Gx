#pragma once

#include <string>

#include <SDL.h>
#include <SDL_ttf.h>

#include "Display.h"

class Text {
public:

	Text(Display* display, TTF_Font* font);
	~Text();

	void setText(std::string text);
	std::string getText();

	void setPosition(SDL_Point position);
	SDL_Point getPosition();

	void setAngle(float angle);
	float getAngle();

	SDL_Texture* getTexture();

	void setColor(SDL_Color color);
	SDL_Color getColor();

	int getWith();
	int getHeight();

private:

	Display* display;
	TTF_Font* font;

	std::string text = "notext";
	SDL_Texture* texture = nullptr;

	SDL_Point position;
	float angle;
	
	int width;
	int height;

	SDL_Color color = { 255, 255, 255 };

	void buildTexture();

};
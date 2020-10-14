#include "MenuGameState.h"

MenuGameState::MenuGameState(Display* display, GameHandler* gamehandler): Gamestate(display, gamehandler)
{
	this->font = TTF_OpenFont(FONT.c_str(), 32);

	this->textRun = new Text(this->display, this->font);
	this->textRun->setColor({ 100,0,0 });
	this->textRun->setText("Start Game");

	this->textOptions = new Text(this->display, this->font);
	this->textOptions->setColor({ 100,0,0 });
	this->textOptions->setText("Options");

	this->textQuit = new Text(this->display, this->font);
	this->textQuit->setColor({ 100,0,0 });
	this->textQuit->setText("Quit");

}

MenuGameState::~MenuGameState()
{
}

void MenuGameState::initialize()
{
	
}

bool upWasPressed = false;
bool downWasPressed = false;

void MenuGameState::update(InputBuffer input, Uint32 delta)
{
	if (input.isPressed(SDL_SCANCODE_UP)) upWasPressed = true;
	
	if (!input.isPressed(SDL_SCANCODE_UP) && upWasPressed) {
		this->selection--;
		if (this->selection < 0) {
			this->selection = 2;
		}
		upWasPressed = false;
	}

	if (input.isPressed(SDL_SCANCODE_DOWN)) downWasPressed = true;

	if (!input.isPressed(SDL_SCANCODE_DOWN) && downWasPressed) {
		this->selection++;
		if (this->selection > 2) {
			this->selection = 0;
		}
		downWasPressed = false;
	}

	this->textRun->setColor({ 100,0,0 });
	this->textOptions->setColor({ 100,0,0 });
	this->textQuit->setColor({ 100,0,0 });

	switch (this->selection) {
	case 0: this->textRun->setColor({ 255,0,0 }); break;
	case 1: this->textOptions->setColor({ 255,0,0 }); break;
	case 2: this->textQuit->setColor({ 255,0,0 }); break;
	}

	this->textRun->setText("Start Game");
	this->textOptions->setText("Options");
	this->textQuit->setText("Quit");

}

void MenuGameState::render()
{

	
	this->target->x = 100;
	this->target->y = 100;
	this->gameHandler->render(this->textRun, this->target);

	this->target->x = 100;
	this->target->y = 130;
	this->gameHandler->render(this->textOptions, this->target);

	this->target->x = 100;
	this->target->y = 160;
	this->gameHandler->render(this->textQuit, this->target);
}



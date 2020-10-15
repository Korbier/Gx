#include "MainMenuGamestate.h"

MainMenuGamestate::MainMenuGamestate(Display* display, GameHandler* gamehandler): MenuGamestate(display, gamehandler)
{
	this->addItem(0, "Start");
	this->addItem(1, "Options");
	this->addItem(2, "Quit");
}

MainMenuGamestate::~MainMenuGamestate()
{
}

void MainMenuGamestate::onReturnPressed()
{
	switch (this->getSelection()) {
	case 0: this->gameHandler->push(new LevelGameState(this->display, this->gameHandler)); break;
	case 2: this->gameHandler->stop(); break;
	}
}

void MainMenuGamestate::render()
{
	this->gameHandler->render({ 0, 0, this->display->getWidth(), this->display->getHeight() }, true, 0, 0, 0, SDL_ALPHA_OPAQUE);
	MenuGamestate::render();
}

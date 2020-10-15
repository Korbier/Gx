#include "InGameMenuGamestate.h"

InGameMenuGameState::InGameMenuGameState(Display* display, GameHandler* gamehandler): MenuGamestate(display, gamehandler)
{
	this->addItem(0, "Resume");
	this->addItem(1, "Options");
	this->addItem(2, "Quit to start screen");
	this->addItem(3, "Quit Game");
}

InGameMenuGameState::~InGameMenuGameState()
{
}

void InGameMenuGameState::onReturnPressed()
{
	switch (this->getSelection()) {
	case 0: this->gameHandler->pop(); break;
	case 2: this->gameHandler->pop( 2 ); break;
	case 3: this->gameHandler->stop(); break;
	//case 2: this->gameHandler->stop(); break;
	}
}

void InGameMenuGameState::render()
{
	this->gameHandler->render({ 0, 0, this->display->getWidth(), this->display->getHeight() }, true, 0, 0, 0, 128);
	MenuGamestate::render();
}


#include "MenuGameState.h"

MenuGamestate::MenuGamestate(Display* display, GameHandler* gamehandler): Gamestate(display, gamehandler)
{
	this->font = TTF_OpenFont(FONT.c_str(), 32);
}

MenuGamestate::~MenuGamestate()
{
}

void MenuGamestate::initialize()
{
	
}

bool upWasPressed = false;
bool downWasPressed = false;

void MenuGamestate::update(InputBuffer input, Uint32 delta)
{
	if (input.isPressed(SDL_SCANCODE_UP))     this->wasUpPressed    = true;
	if (input.isPressed(SDL_SCANCODE_DOWN))   this->wasDownPressed  = true;
	if (input.isPressed(SDL_SCANCODE_LEFT))   this->wasLeftPressed  = true;
	if (input.isPressed(SDL_SCANCODE_RIGHT))  this->wasRightPressed = true;
	if (input.isPressed(SDL_SCANCODE_RETURN)) this->wasReturnPressed = true;

	if (!input.isPressed(SDL_SCANCODE_UP) && this->wasUpPressed && !this->isCleanUpRequested()) {
		if (this->selection == 0) {
			this->selection = this->items.size() - 1;
		} else {
			this->selection--;
		}
		this->wasUpPressed = false;
		this->onUpPressed();
	}

	if (!input.isPressed(SDL_SCANCODE_DOWN) && this->wasDownPressed && !this->isCleanUpRequested()) {
		if (this->selection == this->items.size() - 1) {
			this->selection = 0; 
		} else {
			this->selection++;
		}
		this->wasDownPressed = false;
		this->onDownPressed();
	}

	if (!input.isPressed(SDL_SCANCODE_LEFT) && this->wasLeftPressed && !this->isCleanUpRequested()) {
		this->wasLeftPressed = false;
		this->onLeftPressed();
	}

	if (!input.isPressed(SDL_SCANCODE_RIGHT) && this->wasRightPressed && !this->isCleanUpRequested()) {
		this->wasRightPressed = false;
		this->onRightPressed();
	}

	if (!input.isPressed(SDL_SCANCODE_RETURN) && this->wasReturnPressed && !this->isCleanUpRequested()) {
		this->wasReturnPressed = false;
		this->onReturnPressed();
	}

	//Clear items color
	if (!this->isCleanUpRequested()) {
		this->clearItems();
		this->enlightSelection();
	}

}

void MenuGamestate::render()
{
	this->renderItems();
}

void MenuGamestate::addItem(int selector, std::string text)
{
	Text* textCmp = new Text(this->display, this->font);
	textCmp->setColor({ 100,0,0 });
	textCmp->setText(text);
	this->items[selector] = textCmp;
}

void MenuGamestate::onUpPressed()
{
}

void MenuGamestate::onDownPressed()
{
}

void MenuGamestate::onRightPressed()
{
}

void MenuGamestate::onLeftPressed()
{
}

void MenuGamestate::onReturnPressed()
{
}

unsigned int MenuGamestate::getSelection()
{
	return this->selection;
}

void MenuGamestate::clearItems()
{
	for (unsigned int i = 0; i < this->items.size(); i++) {
		this->items[i]->setColor({ 100,0,0 });
	}
}

void MenuGamestate::renderItems()
{
	for (unsigned int i = 0; i < this->items.size(); i++) {
		this->target->x = 100;
		this->target->y = 100 + 30 * i;
		this->gameHandler->render(this->items[i], this->target);
	}
}

void MenuGamestate::enlightSelection()
{
	if (this->items.size() > 0 && this->selection >= 0 && this->selection < this->items.size() ) {
		this->items[this->selection]->setColor({ 255,0,0 });
	}
}




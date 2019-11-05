#include "Gamestate.h"

Gamestate::Gamestate(Display* display, GameHandler* gamehandler)
{
	this->display     = display;
	this->gameHandler = gamehandler;

	this->target = new SDL_Rect();
	this->target->w = this->target->h = TILE_SIZE;

	this->tileset = new Tileset();
	this->tileset2 = new Tileset();

	this->map = new Map();

	this->camera = new Camera();

	this->camera->setPosition({ 0.f, 0.f });
	this->camera->setSize(SCREEN_WIDTH, SCREEN_HEIGHT);

	this->bDesc = new BulletDescriptor(
		new AnimatedTexture(this->gameHandler->getTexture(BULLET_SPRITESHEET), 20),
		new AnimatedTexture(this->gameHandler->getTexture(BULLET_SPRITESHEET), 20)
	);

	this->bGen = new BulletGenerator(this->bDesc);

}

Gamestate::~Gamestate()
{
	delete this->target;
	delete this->tileset;
	delete this->tileset2;
	delete this->map;
}

void Gamestate::initialize() {

	int height = 300;
	int width  = 300;

	this->tank = new Sprite(new AnimatedTexture(this->gameHandler->getTexture(TANK_SPRITESHEET), 20), { 0.f,0.f }, { 32,32 });
	this->tank->setVelocity({ 200.f, 200.f });
	this->tank->getTexture()->addFrame( 0, 0, 32, 32);
	this->tank->getTexture()->addFrame(32, 0, 32, 32);
	this->tank->getTexture()->addFrame(64, 0, 32, 32);
	this->tank->getTexture()->addFrame(96, 0, 32, 32);

	this->tileset->loadTileset(this->gameHandler->getTexture(TILESET), 32);
	this->tileset2->loadTileset(this->gameHandler->getTexture(TILESET2), 32);

	this->map->addReference(0, this->tileset2,  false, 0, 0);
	this->map->addReference(1, this->tileset,  true, false);
	this->map->addReference(2, this->tileset2, false, true);

	std::vector<std::vector<int>> m;

	for (int i = 0; i < width; i++) {
		std::vector<int> row;
		for (int j = 0; j < height; j++) {
			row.push_back(0);
		}
		m.push_back(row);
	}

	this->map->setData(m, width, height);

}


void Gamestate::update(InputBuffer input, Uint32 delta )
{

	SDL_Point mouse;
	input.mousePosition(&mouse);
	camera->toWorldView(&mouse);
		
	if ( input.isMouseLeftPressed() ) {
		if (input.isPressed(SDL_SCANCODE_0)) {
			map->toMapView(&mouse);
			map->setData(mouse.x, mouse.y, 0);
		}
		else if (input.isPressed(SDL_SCANCODE_1)) {
			map->toMapView(&mouse);
			map->setData(mouse.x, mouse.y, 1);
		}
		else if (input.isPressed(SDL_SCANCODE_2)) {
			map->toMapView(&mouse);
			map->setData(mouse.x, mouse.y, 2);
		}
		else {

			BOOST_LOG_TRIVIAL(info) << "Mouse : " << mouse.x << "," << mouse.y << "; tank : " << tank->getPosition().x << "," << tank->getPosition().y;

			float Ax = tank->getPosition().x + tank->getSize().x / 2;
			float Ay = tank->getPosition().y + tank->getSize().y / 2;

			float Bx = mouse.x;
			float By = mouse.y;

			float x = Bx - Ax;
			float y = By - Ay;

			this->bGen->fire( atan2(x, y * -1) * 180 / M_PI );

		}
	}

	
	float xVal = 0;
	float yVal = 0;

	/* Tank update from keyboard */
	if (input.isPressed(SDL_SCANCODE_RIGHT)) xVal = this->tank->getVelocity().x * (delta / 1000.f);
	if (input.isPressed(SDL_SCANCODE_LEFT))  xVal = -1 * this->tank->getVelocity().x * (delta / 1000.f);
	if (input.isPressed(SDL_SCANCODE_UP))    yVal = -1 * this->tank->getVelocity().y * (delta / 1000.f);
	if (input.isPressed(SDL_SCANCODE_DOWN))  yVal = this->tank->getVelocity().y * (delta / 1000.f);

	if (xVal != 0) {
		this->tank->move({ xVal, 0 });
		if (this->map->collide(this->tank)) {
			this->tank->move({ -xVal, 0 });
		}
	}

	if (yVal != 0) {
		this->tank->move({ 0, yVal });
		if (this->map->collide(this->tank)) {
			this->tank->move({ 0, -yVal });
		}
	}
	
	this->map->boundToMap(this->tank);

	
	bool animateTank = true;

	if (xVal > 0) {
		if (yVal > 0)      this->tank->setAngle(135.0);
		else if (yVal < 0) this->tank->setAngle(45.0);
		else               this->tank->setAngle(90.0);
	}
	else if (xVal < 0) {
		if (yVal > 0)      this->tank->setAngle(225.0);
		else if (yVal < 0) this->tank->setAngle(315.0);
		else               this->tank->setAngle(270.0);
	}
	else {
		if (yVal > 0)      this->tank->setAngle(180.0);
		else if (yVal < 0) this->tank->setAngle(0.0);
		else {
			animateTank = false;
		}
	}

	if (animateTank) {
		this->tank->getTexture()->animate();
	}

	/*
	 * Camera manuelle
	 */
	/*
	xVal = yVal = 0;
	if (input->isPressed(SDL_SCANCODE_KP_6))  xVal = 600 * (delta / 1000.f);
	if (input->isPressed(SDL_SCANCODE_KP_4))  xVal = -1 * 600 * (delta / 1000.f);
	if (input->isPressed(SDL_SCANCODE_KP_8))  yVal = -1 * 600 * (delta / 1000.f);
	if (input->isPressed(SDL_SCANCODE_KP_2))  yVal = 600 * (delta / 1000.f);
	this->camera->setPosition(xVal, yVal);
	*/

	/*
	 * Camera centre sur le sprite
	 */
	xVal = this->tank->getPosition().x + (32 / 2) - this->camera->getSize().x / 2;
	yVal = this->tank->getPosition().y + (32 / 2) - this->camera->getSize().y / 2;

	/*
	* Limitation à la zone de jeu
	*/
	if (xVal < 0) xVal = 0.f;
	if (yVal < 0) yVal = 0.f;
	if (xVal + this->camera->getSize().x > this->map->getWidth() * 32)  xVal = (float) this->map->getWidth() * 32 - this->camera->getSize().x;
	if (yVal + this->camera->getSize().y > this->map->getHeight() * 32) yVal = (float) this->map->getHeight() * 32 - this->camera->getSize().y;

	this->camera->setPosition({ xVal, yVal });


	/** Bullet engine **/
	this->bGen->setPosition(this->tank->getPosition());
	this->bGen->setDirection(this->tank->getAngle());
	this->bGen->update(delta);
	
}

void Gamestate::render()
{

	int minx, maxx, miny, maxy;
	minx = (int) this->camera->getPosition().x / 32;
	miny = (int) this->camera->getPosition().y / 32;
	maxx = (int) (this->camera->getPosition().x + this->camera->getSize().x) / 32;
	maxy = (int) (this->camera->getPosition().y + this->camera->getSize().y) / 32;

	if (minx < 0) minx = 0;
	if (miny < 0) miny = 0;
	if (maxx >= this->map->getWidth())  maxx = this->map->getWidth() - 1;
	if (maxy >= this->map->getHeight()) maxy = this->map->getHeight() - 1;

	int count = 0;
	for (int i = minx; i <= maxx; i++) {
		for (int j = miny; j <= maxy; j++) {

			this->target->x = i * 32;
			this->target->y = j * 32;

			this->camera->toCameraView( this->target );

			Tile* mTile = this->map->getTileAt(i, j);
			this->gameHandler->render(mTile->getTile(), mTile->getAngle(), target);

			count++;

		}
	}

	this->target->x = (int)this->tank->getPosition().x;
	this->target->y = (int)this->tank->getPosition().y;
	this->camera->toCameraView(this->target);

	this->gameHandler->render(this->tank, this->target);
	
	std::vector<Bullet*> bullets = this->bGen->getBulletsToRender();

	for (std::vector<Bullet*>::iterator it = bullets.begin(); it != bullets.end(); ++it) {
		this->target->x = (int) (*it)->getPosition().x;
		this->target->y = (int) (*it)->getPosition().y;
		this->camera->toCameraView(this->target);
		this->gameHandler->render(*it, this->target);
	}

}

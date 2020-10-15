#include "LevelGameState.h"

LevelGameState::LevelGameState(Display* display, GameHandler* gamehandler): Gamestate(display, gamehandler)
{

	std::cout << "construct";

	this->tileset = new Tileset();
	this->tileset2 = new Tileset();

	this->map = new Map();

	this->camera = new Camera();

	this->camera->setPosition({ 0.f, 0.f });
	this->camera->setSize(SCREEN_WIDTH, SCREEN_HEIGHT);

	this->bDesc = new BulletDescriptor(
		new AnimatedTexture(this->gameHandler->getTexture(BULLET_SPRITESHEET), 20),
		new AnimatedTexture(this->gameHandler->getTexture(EXPLOSION_SPRITESHEET), 10)
	);

	this->bDesc->getExplosionTexture()->addFrame(0, 0, 32, 32);
	this->bDesc->getExplosionTexture()->addFrame(32, 0, 32, 32);
	this->bDesc->getExplosionTexture()->addFrame(64, 0, 32, 32);
	this->bDesc->getExplosionTexture()->addFrame(96, 0, 32, 32);
	this->bDesc->getExplosionTexture()->addFrame(128, 0, 32, 32);

	this->bDesc->getExplosionTexture()->addFrame(0, 32, 32, 32);
	this->bDesc->getExplosionTexture()->addFrame(32, 32, 32, 32);
	this->bDesc->getExplosionTexture()->addFrame(64, 32, 32, 32);
	this->bDesc->getExplosionTexture()->addFrame(96, 32, 32, 32);
	this->bDesc->getExplosionTexture()->addFrame(128, 32, 32, 32);

	this->bDesc->getExplosionTexture()->addFrame(0, 64, 32, 32);
	this->bDesc->getExplosionTexture()->addFrame(32, 64, 32, 32);
	this->bDesc->getExplosionTexture()->addFrame(64, 64, 32, 32);
	this->bDesc->getExplosionTexture()->addFrame(96, 64, 32, 32);
	this->bDesc->getExplosionTexture()->addFrame(128, 64, 32, 32);

	this->bDesc->getExplosionTexture()->addFrame(0, 96, 32, 32);
	this->bDesc->getExplosionTexture()->addFrame(32, 96, 32, 32);
	this->bDesc->getExplosionTexture()->addFrame(64, 96, 32, 32);
	this->bDesc->getExplosionTexture()->addFrame(96, 96, 32, 32);
	this->bDesc->getExplosionTexture()->addFrame(128, 96, 32, 32);

	this->bDesc->getExplosionTexture()->addFrame(0, 128, 32, 32);
	this->bDesc->getExplosionTexture()->addFrame(32, 128, 32, 32);
	this->bDesc->getExplosionTexture()->addFrame(64, 128, 32, 32);
	this->bDesc->getExplosionTexture()->addFrame(96, 128, 32, 32);
	this->bDesc->getExplosionTexture()->addFrame(128, 128, 32, 32);

	this->bGen = new BulletGenerator(this->bDesc);

	this->font = TTF_OpenFont(FONT.c_str(), 32);
	this->text = new Text(this->display, this->font);
	this->text->setColor({ 100,0,0 });

}

LevelGameState::~LevelGameState()
{
	delete this->target;
	delete this->tileset;
	delete this->tileset2;
	delete this->map;
	delete this->tank;
	delete this->canon;
	delete this->text;
}

void LevelGameState::initialize()
{

	int height = 300;
	int width = 300;

	this->tank = new Sprite(new AnimatedTexture(this->gameHandler->getTexture(TANK_SPRITESHEET), 20), { 0.f,0.f }, { 32,32 });
	this->tank->setVelocity({ 200.f, 200.f });
	this->tank->getTexture()->addFrame(0, 0, 32, 32);
	this->tank->getTexture()->addFrame(32, 0, 32, 32);
	this->tank->getTexture()->addFrame(64, 0, 32, 32);
	this->tank->getTexture()->addFrame(96, 0, 32, 32);

	this->canon = new Sprite(new AnimatedTexture(this->gameHandler->getTexture(CANON_SPRITESHEET), 20), { 0.f,0.f }, { 32,32 });
	this->canon->getTexture()->addFrame(0, 0, 32, 32);

	this->tileset->loadTileset(this->gameHandler->getTexture(TILESET), 32);
	this->tileset2->loadTileset(this->gameHandler->getTexture(TILESET2), 32);

	this->map->addReference(0, this->tileset2, false, 0, 0);
	this->map->addReference(1, this->tileset, true, false);
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

void LevelGameState::update(InputBuffer input, Uint32 delta)
{

	if (input.isPressed(SDL_SCANCODE_ESCAPE)) {
		this->gameHandler->push(new InGameMenuGameState(this->display, this->gameHandler));
		return;
	}

	SDL_Point mouse;
	input.mousePosition(&mouse);
	camera->toWorldView(&mouse);

	float Ax = tank->getPosition().x + tank->getSize().x / 2;
	float Ay = tank->getPosition().y + tank->getSize().y / 2;

	float Bx = mouse.x;
	float By = mouse.y;

	float x = Bx - Ax;
	float y = By - Ay;

	float mouseAngle = (double)atan2(x, y * -1) * 180 / M_PI; //Angle tank/mouse
	this->canon->setAngle(mouseAngle);

	if (input.isMouseLeftPressed()) {

		if (input.isPressed(SDL_SCANCODE_1)) {
			map->toMapView(&mouse);
			map->setData(mouse.x, mouse.y, 0);
		}
		else if (input.isPressed(SDL_SCANCODE_2)) {
			map->toMapView(&mouse);
			map->setData(mouse.x, mouse.y, 1);
		}
		else if (input.isPressed(SDL_SCANCODE_3)) {
			map->toMapView(&mouse);
			map->setData(mouse.x, mouse.y, 2);
		}
		else {
			this->bGen->fire(mouseAngle);
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
		this->tank->move({ this->map->checKCollisionX(this->tank, xVal), 0 });
	}

	if (yVal != 0) {
		this->tank->move({ 0, this->map->checKCollisionY(this->tank, yVal) });
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

	this->canon->setPosition(this->tank->getPosition());

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
	if (xVal + this->camera->getSize().x > this->map->getWidth() * 32)  xVal = (float)this->map->getWidth() * 32 - this->camera->getSize().x;
	if (yVal + this->camera->getSize().y > this->map->getHeight() * 32) yVal = (float)this->map->getHeight() * 32 - this->camera->getSize().y;

	this->camera->setPosition({ xVal, yVal });

	/** Bullet engine **/
	this->bGen->setPosition(this->tank->getPosition());
	this->bGen->setDirection(this->tank->getAngle());
	this->bGen->update(this->map, delta);

	/** Bots **/
	/*
	for (std::vector<Bot*>::iterator it = this->bots.begin(); it != this->bots.end(); ++it) {
		(*it)->update(delta);
	}
	*/
	this->text->setText("Bullets " + std::to_string(this->bGen->getBulletsToRender().size()) + " - Bots " + std::to_string(this->bots.size()));


}

void LevelGameState::render()
{

	int minx, maxx, miny, maxy;
	minx = (int)this->camera->getPosition().x / 32;
	miny = (int)this->camera->getPosition().y / 32;
	maxx = (int)(this->camera->getPosition().x + this->camera->getSize().x) / 32;
	maxy = (int)(this->camera->getPosition().y + this->camera->getSize().y) / 32;

	if (minx < 0) minx = 0;
	if (miny < 0) miny = 0;
	if (maxx >= this->map->getWidth())  maxx = this->map->getWidth() - 1;
	if (maxy >= this->map->getHeight()) maxy = this->map->getHeight() - 1;

	int count = 0;
	for (int i = minx; i <= maxx; i++) {
		for (int j = miny; j <= maxy; j++) {

			this->target->x = i * 32;
			this->target->y = j * 32;

			this->camera->toCameraView(this->target);

			Tile* mTile = this->map->getTileAt(i, j);
			this->gameHandler->render(mTile->getTile(), mTile->getAngle(), target);

			count++;

		}
	}

	this->target->x = (int)this->tank->getPosition().x;
	this->target->y = (int)this->tank->getPosition().y;
	this->camera->toCameraView(this->target);

	this->gameHandler->render(this->tank, this->target);
	this->gameHandler->render(this->canon, this->target);

	for (std::vector<Bot*>::iterator it = this->bots.begin(); it != this->bots.end(); ++it) {
		this->target->x = (int)(*it)->getPosition().x;
		this->target->y = (int)(*it)->getPosition().y;
		this->camera->toCameraView(this->target);
		this->gameHandler->render((*it), this->target);
	}

	std::vector<Bullet*> bullets = this->bGen->getBulletsToRender();

	for (std::vector<Bullet*>::iterator it = bullets.begin(); it != bullets.end(); ++it) {
		if ((*it)->isRenderable()) {
			this->target->x = (int)(*it)->getPosition().x;
			this->target->y = (int)(*it)->getPosition().y;
			this->camera->toCameraView(this->target);
			this->gameHandler->render(*it, this->target);
		}
	}


	this->target->x = 10;
	this->target->y = 10;
	this->gameHandler->render(this->text, this->target);
	/*
	for (JPS::PathVector::iterator it = this->path.begin(); it != this->path.end(); ++it) {
		this->gameHandler->render({ (int)it->x * 32, (int)it->y * 32, 32, 32 });
		//BOOST_LOG_TRIVIAL(error) << it->x << "," << it->y;

	}
	*/
	/*
		if (this->aStarNode != nullptr) {

			std::shared_ptr<Node> current = this->aStarNode;
			std::shared_ptr<Node> parent = current->parent;

			this->gameHandler->render({ current->cell.x * 32, current->cell.y * 32, 32, 32 });

			while (parent != nullptr) {
				SDL_Rect r = { current->cell.x * 32, current->cell.y * 32 , parent->cell.x * 32, parent->cell.y * 32 };
				this->camera->toCameraView( &r);

				this->gameHandler->render({ r.x + 16, r.y + 16 }, { r.w + 16, r.h + 16});
				this->gameHandler->render({ current->cell.x * 32, current->cell.y * 32, 32, 32 });
				current = parent;
				parent  = current->parent;
			}

		}
	*/
}

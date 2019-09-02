#pragma once

#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 480
#define FRAMES_PER_SECOND 60
#define TICKS_PER_FRAME 1000 / FRAMES_PER_SECOND

class GameHandler;
class Display;
class Gamestate;
class Timer;
class TextureManager;

class Game
{
public:
	
	void initialize();
	void finalize();

	void run();
	void stop();

	bool isRunning();

	TextureManager* getTextureManager();

private:

	bool         running  = false;
	Display*     display  = nullptr;
	Gamestate*   state    = nullptr; //TODO Mettre en place le gamestate manager
	GameHandler* gHandler = nullptr;

	TextureManager* textureManager = nullptr;

	int frame = 0;
	Timer* capTimer = nullptr;

	void input();
	void render();

};


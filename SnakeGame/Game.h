/**
 @file    maiin.cpp
 @author  Yebeltal Asseged
 @version 1.1

 **/


#ifndef GAME_H
#define GAME_H

#include "Engine.h"

class Snake;
class Food;
class Powerup;

class Game {
private:
	SDL_Surface* screen;
	SDL_Surface* screenShot;
	SDL_Event event;

	Engine::Timer_FixedFPS timer;
	int FPS;

	bool stopApp;

	Engine::TextManager* textManager;
	SDL_Color textColor;

	Snake* snake1;
	Food* food1;
	Powerup* powerup1;

	void Update();
	void Render( bool flipScreen = true );

	void DrawHUD();

	void GameStart();
	void GameOver();

	void Pause();

public:
	Game();
	~Game();

	int Execute();
};

#endif

/**
 @file    maiin.cpp
 @author  Yebeltal Asseged
 @version 1.1

 **/


#ifndef SNAKE_H
#define SNAKE_H

#include "PowerupManager.h"

#include <vector>

#include "SDL.h"

class Food;
class Powerup;
class BodyPart;

enum {
	DIR_UP,
	DIR_DOWN,
	DIR_LEFT,
	DIR_RIGHT
};

class Snake {
private:
	std::vector < BodyPart > body;

	SDL_Surface* headTexture;
	SDL_Surface* bodyTexture;

	int direction;
	int bodyPartsToGo;

	PowerupManager powerupManager;

	void Move();
	void HandleCollision( Food* food1, Powerup* powerup1 );
	void AddBodyPart();
	void Reset();

public:
	Snake();
	~Snake();

	int score;
	int lives;
	bool gameOver;

	void Update( Food* food1, Powerup* powerup1 );
	void Render( SDL_Surface* destSurface );

	void SetInput( SDLKey key );
	std::vector < BodyPart >& GetBody();
};

#endif

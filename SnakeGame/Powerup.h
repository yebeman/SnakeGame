/**
 @file    maiin.cpp
 @author  Yebeltal Asseged
 @version 1.1

 **/


#ifndef POWERUP_H
#define POWERUP_H

#include "SDL.h"

#include <vector>

class Snake;
class Food;
class BodyPart;

struct PowerupType {
	std::string name;
	int lifeTime;

	PowerupType() { }
	PowerupType( std::string _name, int _lifeTime );
};


class Powerup {
private:
	std::vector < PowerupType > powerupTypes;
	int numPowerupTypes;
	int powerupType;

	SDL_Surface* throughWallTexture;
	SDL_Surface* duoPointsTexture;
	SDL_Surface* trioPointsTexture;
	SDL_Surface* quattroPointsTexure;

	SDL_Surface* texture;

	int lifeTime;
	int idleTime;

	bool idle;

	Snake* snake1;

	bool PositionFree( Food* food1 );
	void NewPosition( Food* food1 );

public:
	Powerup( Snake* _snake1 );
	~Powerup();

	int X;
	int Y;

	bool alive;

	std::string name;

	void Update( Food* food1 );
	void Render( SDL_Surface* destSurface );

	void Reset();
};

#endif
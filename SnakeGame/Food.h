#ifndef FOOD_H
#define FOOD_H

#include "SDL.h"

#include <string>
#include <vector>

class Snake;
class Powerup;
class BodyPart;

class Food {
private:
	SDL_Surface* texture;

	int lifeTime;
	Snake* snake1;

	bool PositionFree( Powerup* powerup1 );

public:
	Food( Snake* _snake1 );
	~Food();

	int X;
	int Y;

	void NewPosition( Powerup* powerup1 );
	void Update( Powerup* powerup1 );
	void Render( SDL_Surface* destSurface );
};

#endif

/**
 @file    maiin.cpp
 @author  Yebeltal Asseged
 @version 1.1

 **/


#include "Powerup.h"
#include "Snake.h"
#include "Food.h"
#include "BodyPart.h"
#include "Engine.h"

const int BOARD_WIDTH = 22;
const int BOARD_HEIGHT = 16;

const int FPS = 7;
const int TICKS_PER_SECOND = 1000;

PowerupType::PowerupType( std::string _name, int _lifeTime ) {
	name = _name;
	lifeTime = _lifeTime;
}

Powerup::Powerup( Snake* _snake1 ) {
	powerupTypes.push_back( PowerupType( "through_wall", 4000 ) );
	powerupTypes.push_back( PowerupType( "duo_points", 4000 ) );
	powerupTypes.push_back( PowerupType( "trio_points", 3500 ) );
	powerupTypes.push_back( PowerupType( "quattro_points", 3000 ) );

	throughWallTexture = Engine::LoadSurface( "data/powerup_through_wall.png" );
	duoPointsTexture = Engine::LoadSurface( "data/powerup_duo_points.png" );
	trioPointsTexture = Engine::LoadSurface( "data/powerup_trio_points.png" );
	quattroPointsTexure = Engine::LoadSurface( "data/powerup_quattro_points.png" );

	numPowerupTypes = 4;

	texture = nullptr;

	lifeTime = 0;
	idleTime = rand() % 4000 + 4000;

	idle = true;
	alive = false;

	snake1 = _snake1;

	X = 0;
	Y = 0;
}

Powerup::~Powerup() {
	SDL_FreeSurface( throughWallTexture );
	SDL_FreeSurface( duoPointsTexture );
	SDL_FreeSurface( trioPointsTexture );
	SDL_FreeSurface( quattroPointsTexure );
}

bool Powerup::PositionFree( Food* food1 ) {
	std::vector < BodyPart >& snakeBody = snake1->GetBody();

	for ( unsigned int i = 0; i < snakeBody.size(); i++ ) {
		if ( X == snakeBody[ i ].X && Y == snakeBody[ i ].Y ) {
			return false;
		}
	}

	return ( X != food1->X && Y != food1->Y );
}

void Powerup::NewPosition( Food* food1 ) {
	powerupType = rand() % numPowerupTypes;

	lifeTime = powerupTypes[ powerupType ].lifeTime;

	if ( powerupTypes[ powerupType ].name == "through_wall" ) {
		texture = throughWallTexture;
	}
	else if ( powerupTypes[ powerupType ].name == "duo_points" ) {
		texture = duoPointsTexture;
	}
	else if ( powerupTypes[ powerupType ].name == "trio_points" ) {
		texture = trioPointsTexture;
	}
	else if ( powerupTypes[ powerupType ].name == "quattro_points" ) {
		texture = quattroPointsTexure;
	}

	name = powerupTypes[ powerupType ].name;

	idleTime = 0;
	idle = false;
	alive = true;

	do {
		X = rand() % BOARD_WIDTH;
		Y = rand() % BOARD_HEIGHT;
	} while ( !PositionFree( food1 ) );
}

void Powerup::Update( Food* food1 ) {
	if ( idle ) {
		idleTime -= TICKS_PER_SECOND / FPS;
		if ( idleTime <= 0 ) {
			NewPosition( food1 );
		}
	}
	else if ( alive ) {
		lifeTime -= TICKS_PER_SECOND / FPS;
		if ( lifeTime <= 0 ) {
			Reset();
		}
	}
}

void Powerup::Render( SDL_Surface* destSurface ) {
	if ( alive && texture ) {
		Engine::DrawSurface( texture, destSurface, X * 30 + 20, Y * 30 + 20 );
	}
}

void Powerup::Reset() {
	idle = true;
	alive = false;

	lifeTime = 0;
	idleTime = rand() % 4000 + 4000;
}
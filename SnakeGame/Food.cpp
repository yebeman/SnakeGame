/**
 @file    maiin.cpp
 @author  Yebeltal Asseged
 @version 1.1

 **/

#include "Food.h"
#include "Snake.h"
#include "Powerup.h"
#include "BodyPart.h"
#include "Engine.h"

#include <ctime>

const int FOOD_LIFE_TIME = 5000;

const int BOARD_WIDTH = 22;
const int BOARD_HEIGHT = 16;

const int FPS = 7;
const int TICKS_PER_SECOND = 1000;

Food::Food( Snake* _snake1 ) {
	texture = Engine::LoadSurface( "data/food.png" );

	snake1 = _snake1;

	NewPosition( nullptr );
}

Food::~Food() {
	SDL_FreeSurface( texture );
}

bool Food::PositionFree( Powerup* powerup1 ) {
	std::vector < BodyPart >& snakeBody = snake1->GetBody();

	for ( unsigned int i = 0; i < snakeBody.size(); i++ ) {
		if ( X == snakeBody[ i ].X && Y == snakeBody[ i ].Y ) {
			return false;
		}
	}

	return ( powerup1 && powerup1->alive ? ( X != powerup1->X && Y != powerup1->Y ) : true );
}

void Food::NewPosition( Powerup* powerup1 ) {
	lifeTime = FOOD_LIFE_TIME;

	do {
		X = rand() % BOARD_WIDTH;
		Y = rand() % BOARD_HEIGHT;
	} while ( !PositionFree( powerup1 ) );
}

void Food::Update( Powerup* powerup1 ) {
	lifeTime -= TICKS_PER_SECOND / FPS;
	if ( lifeTime <= 0 ) {
		NewPosition( powerup1 );
	}
}

void Food::Render( SDL_Surface* destSurface ) {
	Engine::DrawSurface( texture, destSurface, X * 30 + 20, Y * 30 + 20 );
}

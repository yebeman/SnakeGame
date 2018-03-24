/**
 @file    maiin.cpp
 @author  Yebeltal Asseged
 @version 1.1

 **/



#include "Engine.h"
#include "Snake.h"
#include "Food.h"
#include "Powerup.h"
#include "BodyPart.h"

const int BOARD_WIDTH = 22;
const int BOARD_HEIGHT = 16;

const int INITIAL_BODY_PARTS = 3;

Snake::Snake() {
	Reset();

	headTexture = Engine::LoadSurface( "data/snake_head.png" );
	bodyTexture = Engine::LoadSurface( "data/snake_body.png" );

	score = 0;
	lives = 3;
	gameOver = false;
}

Snake::~Snake() {
	SDL_FreeSurface( headTexture );
	SDL_FreeSurface( bodyTexture );
}

void Snake::Move() {
	int headX = body[ 0 ].X;
	int headY = body[ 0 ].Y;

	switch ( direction ) {
	case DIR_UP:
		headY += -1;
		break;
	case DIR_DOWN:
		headY += 1;
		break;
	case DIR_LEFT:
		headX += -1;
		break;
	case DIR_RIGHT:
		headX += 1;
		break;
	}

	body[ 0 ].Update( headX, headY );

	// Check if the throughwall powerup is activated
	if ( powerupManager[ "through_wall" ] ) {
		if ( body[ 0 ].X < 0 ) {
			body[ 0 ].X = BOARD_WIDTH - 1;
		}
		if ( body[ 0 ].X > BOARD_WIDTH - 1 ) {
			body[ 0 ].X = 0;
		}
		if ( body[ 0 ].Y < 0 ) {
			body[ 0 ].Y = BOARD_HEIGHT - 1;
		}
		if ( body[ 0 ].Y > BOARD_HEIGHT - 1 ) {
			body[ 0 ].Y = 0;
		}
	}

	for ( unsigned int i = 1; i < body.size(); i++ ) {
		body[ i ].Update( body[ i - 1 ].oldX, body[ i - 1 ].oldY );
	}
}

void Snake::HandleCollision( Food* food1, Powerup* powerup1 ) {
	// Check for collision with the bounds of the board
	if ( body[ 0 ].X < 0 || body[ 0 ].X > BOARD_WIDTH - 1 || body[ 0 ].Y < 0 || body[ 0 ].Y > BOARD_HEIGHT - 1 ) {
		lives--;
		Reset();

		food1->NewPosition( powerup1 );
		powerup1->Reset();
	}

	// Check for collision with the snake's body
	for ( unsigned int i = 1; i < body.size(); i++ ) {
		if ( body[ 0 ].X == body[ i ].X && body[ 0 ].Y == body[ i ].Y ) {
			lives--;
			Reset();

			food1->NewPosition( powerup1 );
			powerup1->Reset();

			break;
		}
	}

	// Check for collision with the food
	if ( body[ 0 ].X == food1->X && body[ 0 ].Y == food1->Y ) {
		int add = 1;

		if ( powerupManager[ "duo_points" ] ) {
			add *= 2;
		}
		if ( powerupManager[ "trio_points" ] ) {
			add *= 3;
		}
		if ( powerupManager[ "quattro_points" ] ) {
			add *= 4;
		}

		score += add;
		bodyPartsToGo += add;

		food1->NewPosition( powerup1 );
	}

	// Check for collision with the powerup
	if ( powerup1->alive && body[ 0 ].X == powerup1->X && body[ 0 ].Y == powerup1->Y ) {
		powerupManager[ powerup1->name ] = true;
		powerup1->Reset();
	}
}

void Snake::AddBodyPart() {
	body.push_back( BodyPart( body[ body.size() - 1 ].oldX, body[ body.size() - 1 ].oldY ) );
}

void Snake::Reset() {
	// Make the snake 0 parts long
	body.erase( body.begin(), body.end() );

	// And add 4 new parts to it
	for ( int i = 0; i < INITIAL_BODY_PARTS + 1; i++ ) {
		body.push_back( BodyPart( BOARD_WIDTH / 2 - i - 1, BOARD_HEIGHT / 2 ) );
	}

	direction = DIR_RIGHT;
	bodyPartsToGo = 0;

	// Deactivate all powerups
	const std::string powerupNames[ 4 ] = { "through_wall", "duo_points", "trio_points", "quattro_points" };
	for ( int i = 0; i < 4; i++ ) {
		powerupManager[ powerupNames[ i ] ] = false;
	}
}

void Snake::Update( Food* food1, Powerup* powerup1 ) {
	Move();
	HandleCollision( food1, powerup1 );

	if ( lives <= 0 ) {
		gameOver = true;
	}

	if ( bodyPartsToGo > 0 ) {
		AddBodyPart();
		bodyPartsToGo--;
	}

	powerupManager.Update();
}

void Snake::Render( SDL_Surface* destSurface ) {
	// Draw the head
	Engine::DrawSurface( headTexture, destSurface, body[ 0 ].X * 30 + 20, body[ 0 ].Y * 30 + 20 );

	// Draw all bodyparts
	for ( unsigned int i = 1; i < body.size(); i++ ) {
		Engine::DrawSurface( bodyTexture, destSurface, body[ i ].X * 30 + 20, body[ i ].Y * 30 + 20 );
	}
}

void Snake::SetInput( SDLKey key ) {
	switch ( key ) {
	case SDLK_UP:
		direction = DIR_UP;
		break;
	case SDLK_DOWN:
		direction = DIR_DOWN;
		break;
	case SDLK_LEFT:
		direction = DIR_LEFT;
		break;
	case SDLK_RIGHT:
		direction = DIR_RIGHT;
		break;
	}
}

std::vector < BodyPart >& Snake::GetBody() {
	return body;
}

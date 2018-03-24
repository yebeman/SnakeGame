/**
 @file    maiin.cpp
 @author  Yebeltal Asseged
 @version 1.1

 **/


#include "Game.h"
#include "Snake.h"
#include "Food.h"
#include "Powerup.h"

#include <ctime>
#include <sstream>

Game::Game() {
	SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER );
	TTF_Init();

	srand( ( unsigned int ) time( nullptr ) );

	screen = SDL_SetVideoMode( 700, 520, 32, SDL_HWSURFACE | SDL_DOUBLEBUF );
	SDL_WM_SetCaption( "Snake Classic", "Snake Classic" );

	FPS = 7;
	timer = Engine::Timer_FixedFPS( FPS );

	stopApp = false;

	textManager = new Engine::TextManager;
	textManager->AddFont( "data/arista.ttf", 45 );
	textManager->AddFont( "data/arista.ttf", 80 );

	textColor.r = 255;
	textColor.g = 0;
	textColor.b = 0;

	snake1 = new Snake;
	food1 = new Food( snake1 );
	powerup1 = new Powerup( snake1 );
}

Game::~Game() {
	delete textManager;
	delete snake1;
	delete food1;
	delete powerup1;

	TTF_Quit();
	SDL_Quit();
}

void Game::Update() {
	snake1->Update( food1, powerup1 );
	food1->Update( powerup1 );
	powerup1->Update( food1 );
}

void Game::Render( bool flipScreen ) {
	SDL_FillRect( screen, nullptr, 0x0 );

	snake1->Render( screen );
	food1->Render( screen );
	powerup1->Render( screen );

	DrawHUD();

	if ( flipScreen ) {
		SDL_Flip( screen );
	}
}

int Game::Execute() {
	GameStart();

	while ( true ) {
		timer.Start();

		while ( SDL_PollEvent( &event ) ) {
			if ( event.type == SDL_QUIT ) {
				stopApp = true;
				break;
			}
			else if ( event.type == SDL_KEYDOWN ) {
				if ( event.key.keysym.sym == SDLK_ESCAPE ) {
					stopApp = true;
					break;
				}
				else if ( event.key.keysym.sym == SDLK_p ) {
					Pause();
				}
			}

			snake1->SetInput( event.key.keysym.sym );
		}

		if ( stopApp ) {
			break;
		}

		Update();
		if ( snake1->gameOver ) {
			GameOver();
			break;
		}

		Render();

		timer.Delay();
	}

	return 0;
}

void Game::DrawHUD() {
	// The rectangle that holds the offsets and dimensions of the wall parts
	SDL_Rect wallRect;

	// Draw the left vertical part
	wallRect.x = 0;
	wallRect.y = 0;
	wallRect.w = 20;
	wallRect.h = 520;
	SDL_FillRect( screen, &wallRect, 0xFFFF00 );

	// The upper horizontal part
	wallRect.x = 0;
	wallRect.y = 0;
	wallRect.w = 700;
	wallRect.h = 20;
	SDL_FillRect( screen, &wallRect, 0xFFFF00 );

	// The bottom horizontal part
	wallRect.y = 500;
	SDL_FillRect( screen, &wallRect, 0xFFFF00 );

	// The right vertical part
	wallRect.x = 680;
	wallRect.y = 0;
	wallRect.w = 20;
	wallRect.h = 520;
	SDL_FillRect( screen, &wallRect, 0xFFFF00 );
}

void Game::GameStart() {
	SDL_EventState( SDL_KEYDOWN, SDL_IGNORE );

	const std::string messages[ 4 ] = { "3!", "2!", "1!", "Go!" };

	for ( int i = 0; i < 4; i++ ) {
		Render( false );
		textManager->DrawText( messages[ i ], "data/arista.ttf80", textColor, 0, screen->h / 2 - screen->h / 4, true, false, screen );
		SDL_Flip( screen );
		SDL_Delay( 700 );

		if ( i != 3 ) {
			Render();
			SDL_Flip( screen );
			SDL_Delay( 200 );
		}
	}

	SDL_EventState( SDL_KEYDOWN, SDL_ENABLE );
}

void Game::GameOver() {
	SDL_FillRect( screen, nullptr, 0x0 );
	SDL_Flip( screen );

	for ( int i = 0; i < 3; i++ ) {
		textManager->DrawText( "Game Over!", "data/arista.ttf80", textColor, 0, 0, true, true, screen );
		SDL_Flip( screen );
		SDL_Delay( 500 );

		SDL_FillRect( screen, nullptr, 0x0 );
		SDL_Flip( screen );

		if ( i != 2 ) {
			SDL_Delay( 500 );
		}
	}
}

void Game::Pause() {
	while ( true ) {
		if ( SDL_PollEvent( &event ) ) {
			if ( event.type == SDL_QUIT ) {
				stopApp = true;
				break;
			}
			else if ( event.type == SDL_KEYDOWN ) {
				if ( event.key.keysym.sym == SDLK_ESCAPE ) {
					stopApp = true;
					break;
				}
				else if ( event.key.keysym.sym == SDLK_p ) {
					break;
				}
			}
		}

		Render( false );
		textManager->DrawText( "Game Paused", "data/arista.ttf80", textColor, 0, screen->h / 2 - screen->h / 4, true, false, screen );
		SDL_Flip( screen );
	}

	timer.Start();
}

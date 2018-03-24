/**
 @file    maiin.cpp
 @author  Yebeltal Asseged
 @version 1.1

 **/


#include "Engine.h"

namespace Engine {

	const int TICKS_PER_SECOND = 1000;

	Timer_FixedFPS::Timer_FixedFPS() {
	}

	Timer_FixedFPS::Timer_FixedFPS( int fps ) {
		FPS = fps;
		startTime = frameTime = 0;
	}

	void Timer_FixedFPS::Start() {
		startTime = SDL_GetTicks();
	}

	void Timer_FixedFPS::Delay() {
		frameTime = SDL_GetTicks() - startTime;

		if ( frameTime < TICKS_PER_SECOND / FPS ) {
			SDL_Delay( ( TICKS_PER_SECOND / FPS ) - frameTime );
		}
	}

}
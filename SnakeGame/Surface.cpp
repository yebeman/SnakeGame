/**
 @file    maiin.cpp
 @author  Yebeltal Asseged
 @version 1.1

 **/

#include "Engine.h"

#include "SDL_image.h"

#include <Windows.h>

namespace Engine {

	SDL_Surface* LoadSurface( std::string fileName ) {
		SDL_Surface* loadedSurface = IMG_Load( fileName.c_str() );
		SDL_Surface* optimizedSurface = SDL_DisplayFormat( loadedSurface );
		SDL_FreeSurface( loadedSurface );

		return optimizedSurface;
	}

	SDL_Surface* LoadSurface( std::string fileName, Uint8 R, Uint8 G, Uint8 B ) {
		SDL_Surface* loadedSurface = IMG_Load( fileName.c_str() );
		SDL_Surface* optimizedSurface = SDL_DisplayFormat( loadedSurface );
		SDL_FreeSurface( loadedSurface );

		Uint32 colorkey = SDL_MapRGB( optimizedSurface->format, R, G, B );
		SDL_SetColorKey( optimizedSurface, SDL_SRCCOLORKEY, colorkey );

		return optimizedSurface;
	}

	void DrawSurface( SDL_Surface* source, SDL_Surface* destination, int x, int y, SDL_Rect* clip ) {
		SDL_Rect offset;
		offset.x = x;
		offset.y = y;

		SDL_BlitSurface( source, clip, destination, &offset );
	}

}
/**
 @file    maiin.cpp
 @author  Yebeltal Asseged
 @version 1.1

 **/


#include "Engine.h"

#include <sstream>

namespace Engine {

	TextManager::TextManager() {
		textSurface = nullptr;
	}

	TextManager::~TextManager() {
		SDL_FreeSurface( textSurface );
	}

	bool TextManager::FontExists( std::string fontName ) {
		for ( unsigned int i = 0; i < fontNames.size(); i++ ) {
			if ( fontName == fontNames[ i ] ) {
				return true;
			}
		}

		return false;
	}

	TTF_Font* TextManager::GetFont( std::string fontName ) {
		for ( unsigned int i = 0; i < fontNames.size(); i++ ) {
			if ( fontName == fontNames[ i ] ) {
				return fonts[ i ];
			}
		}

		return nullptr;
	}

	void TextManager::AddFont( std::string fileName, int fontSize ) {
		TTF_Font* font = TTF_OpenFont( fileName.c_str(), fontSize );

		std::stringstream ss;
		ss << fileName << fontSize;

		if ( !FontExists( ss.str() ) ) {
			fontNames.push_back( ss.str() );
			fonts.push_back( font );
		}
	}

	void TextManager::DrawText( std::string text, std::string fontName, SDL_Color color, int x, int y, bool xCentered, bool yCentered, SDL_Surface* destSurface ) {
		TTF_Font* font = GetFont( fontName );

		if ( font ) {
			textSurface = TTF_RenderText_Blended( font, text.c_str(), color );

			if ( xCentered ) {
				x = destSurface->w / 2 - textSurface->w / 2;
			}
			if ( yCentered ) {
				y = destSurface->h / 2 - textSurface->h / 2;
			}

			DrawSurface( textSurface, destSurface, x, y );
		}
	}

}

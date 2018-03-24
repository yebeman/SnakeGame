#ifndef ENGINE_H
#define ENGINE_H

#include "SDL.h"
#include "SDL_ttf.h"

#include <string>
#include <vector>

namespace Engine {

	// This function loads a surface, converts it to the screen format (with SDL_DisplayFormat())
	// and returns it.
	SDL_Surface* LoadSurface( std::string fileName );

	// This function loads a surface, converts it to the screen format (with SDL_DisplayFormat()),
	// colorkeys it with the passed color and returns it.
	SDL_Surface* LoadSurface( std::string fileName, Uint8 R, Uint8 G, Uint8 B );

	// This function draws the passed surface to the passed surface, on the passed coordinate,
	// using the passed clip.
	void DrawSurface( SDL_Surface* source, SDL_Surface* destination, int x, int y, SDL_Rect* clip = nullptr );

	// A time management class with fixed FPS.
	// The Start() function should be called at the start of each frame,
	// Delay() at the end.
	// Use it to cap the framerate.
	class Timer_FixedFPS {
	private:
		int FPS;          // The desired framerate.

		Uint32 startTime; // Stores the time at the start of the frame.
		Uint32 frameTime; // Stores the current time minus startTime, so the time it took the PC to render the frame.

	public:
		Timer_FixedFPS();
		Timer_FixedFPS( int fps );

		void Start(); // Sets startTime to the current frame.
		void Delay(); // Delays the desired time.
	};

	// A textmanager class, using .ttf fonts.
	// Much easier than using SDL_ttf directly.
	class TextManager {
	private:
		std::vector < std::string > fontNames;
		std::vector < TTF_Font* > fonts;

		SDL_Surface* textSurface;

		bool FontExists( std::string fontName );
		TTF_Font* GetFont( std::string fontName );

	public:
		TextManager();
		~TextManager();

		void AddFont( std::string fileName, int fontSize );
		void DrawText( std::string text, std::string fontName, SDL_Color color, int x, int y, bool xCentered, bool yCentered, SDL_Surface* destSurface );
	};

}

#endif

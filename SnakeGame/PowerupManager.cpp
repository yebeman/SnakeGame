/**
 @file    maiin.cpp
 @author  Yebeltal Asseged
 @version 1.1

 **/


#include "PowerupManager.h"

const int TICKS_PER_SECOND = 1000;
const int FPS = 7;

PowerupManager::PowerupManager() {
	powerupList.push_back( PowerupInfo( "through_wall", false, -1 ) );
	powerupList.push_back( PowerupInfo( "duo_points", false, 15000 ) );
	powerupList.push_back( PowerupInfo( "trio_points", false, 10000 ) );
	powerupList.push_back( PowerupInfo( "quattro_points", false, 5000 ) );
}

void PowerupManager::Update() {
	for ( unsigned int i = 0; i < powerupList.size(); i++ ) {
		if ( powerupList[ i ].activated && powerupList[ i ].activeTime != -1 ) {
			powerupList[ i ].remainingTime -= TICKS_PER_SECOND / FPS;
			if ( powerupList[ i ].remainingTime <= 0 ) {
				powerupList[ i ].activated = false;
				powerupList[ i ].remainingTime = powerupList[ i ].activeTime;
			}
		}
	}
}

bool& PowerupManager::operator [] ( std::string name ) {
	for ( unsigned int i = 0; i < powerupList.size(); i++ ) {
		if ( powerupList[ i ].name == name ) {
			return powerupList[ i ].activated;
		}
	}

	bool fixMe = false;
	return fixMe;
}
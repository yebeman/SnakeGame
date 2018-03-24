/**
 @file    maiin.cpp
 @author  Yebeltal Asseged
 @version 1.1

 **/


#ifndef POWERUP_MANAGER_H
#define POWERUP_MANAGER_H

#include <string>
#include <vector>

struct PowerupInfo {
	std::string name;
	bool activated;

	int activeTime;
	int remainingTime;

	PowerupInfo() { }
	PowerupInfo( std::string _name, bool _activated, int _activeTime ) : name( _name ), activated( _activated ), activeTime( _activeTime ), remainingTime( _activeTime ) { }
};

class PowerupManager {
private:
	std::vector < PowerupInfo > powerupList;

public:
	PowerupManager();

	void Update();

	bool& operator [] ( std::string name );
};

#endif
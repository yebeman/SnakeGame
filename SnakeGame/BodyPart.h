/**
 @file    maiin.cpp
 @author  Yebeltal Asseged
 @version 1.1

 **/

#ifndef BODY_PART_H
#define BODY_PART_H

class BodyPart {
public:
	BodyPart();
	BodyPart( int x, int y );

	int X;
	int oldX;

	int Y;
	int oldY;

	void Update( int x, int y );
};

#endif

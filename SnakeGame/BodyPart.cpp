/**
 @file    maiin.cpp
 @author  Yebeltal Asseged
 @version 1.1

 **/

#include "BodyPart.h"

BodyPart::BodyPart() {
}

BodyPart::BodyPart( int x, int y ) {
	X = x;
	Y = y;

	oldX = oldY = 0;
}

void BodyPart::Update( int x, int y ) {
	oldX = X;
	oldY = Y;

	X = x;
	Y = y;
}
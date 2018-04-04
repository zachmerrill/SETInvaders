/*
FILE		:	Planet.cpp
PROJECT		:	Graphics, Animation, & Sound - Assignment 1
DATE		:	February 13, 2018
AUTHOR		:	Zach Merrill
DESCRIPTION	:	This file contains the methods for the Planet class.
*/
#include "Planet.h"

/*
METHOD		:	Planet - Constructor
DESCRIPTION	:	This method creates a planet object given x, y, and a SpriteSheet.
PARAMETERS	:	float x - x coordinate
				float y - y coordinate
				SpriteSheet* sprites - SpriteSheet object
RETURNS		:	void
*/
Planet::Planet(float x, float y, SpriteSheet* sprites) {
	this->x = x;
	this->y = y;
	this->sprites = sprites;
}


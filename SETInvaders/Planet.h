/*
FILE		:	Planet.h
PROJECT		:	Graphics, Animation, & Sound - Assignment 1
DATE		:	February 13, 2018
AUTHOR		:	Zach Merrill
*/
#pragma once
#include "Entity.h"

/*
NAME		:	Planet
DESCRIPTION	:	The Planet class defines a Planet based on the Entity class.
				Currently, a planet has no extra attributes from an entity but it is expected
				that in the future it will require modification.
*/
class Planet : public Entity {
public:
	Planet(float x, float y, SpriteSheet* sprites);
};
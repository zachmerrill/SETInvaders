/*
FILE		:	Entity.h
PROJECT		:	Graphics, Animation, & Sound - Assignment 1
DATE		:	February 13, 2018
AUTHOR		:	Zach Merrill
*/
#pragma once
#include "SpriteSheet.h"

/*
NAME		:	Entity
DESCRIPTION	:	The Entity class defines a generic game object within the direct2d space.
				Each entity holds an x,y position, rgba colour scheme and a spritesheet.
*/
class Entity {
public:
	float x;
	float y;
	float r;
	float b;
	float g;
	float a;
	SpriteSheet* sprites;

	Entity();
	~Entity();
	void DrawSprites();
};
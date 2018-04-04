/*
FILE		:	Entity.cpp
PROJECT		:	Graphics, Animation, & Sound - Assignment 1
DATE		:	February 13, 2018
AUTHOR		:	Zach Merrill
DESCRIPTION	:	This file contains the methods for the Entity class.
*/
#include "Entity.h"

/*
METHOD		:	Entity - Constructor
DESCRIPTION	:	This method creates an entity with the default values;
PARAMETERS	:	void
RETURNS		:	void
*/
Entity::Entity() {
	x = 0.0f;
	y = 0.0f;
	r = 1.0f;
	g = 1.0f;
	b = 1.0f;
	a = 1.0f;
	sprites = NULL;
}

/*
METHOD		:	~Entity - Destructor
DESCRIPTION	:	This method deletes the sprite object on deletion of an entity.
PARAMETERS	:	void
RETURNS		:	void
*/
Entity::~Entity() {
	if(sprites) delete sprites;
}

/*
METHOD		:	DrawSprites
DESCRIPTION	:	This method draws the entity's spritesheet.
PARAMETERS	:	void
RETURNS		:	void
*/
void Entity::DrawSprites() {
	if(sprites != NULL) {
		sprites->Draw(x, y);
	}
}

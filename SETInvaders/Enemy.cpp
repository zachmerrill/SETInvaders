/*
FILE		:	Entity.cpp
PROJECT		:	Graphics, Animation, & Sound - Assignment 1
DATE		:	February 13, 2018
AUTHOR		:	Zach Merrill
DESCRIPTION	:	This file contains the methods for the Enemy class.
*/
#include "Enemy.h"

/*
METHOD		:	Enemy - Constructor
DESCRIPTION	:	This method creates an enemy object with default values.
PARAMETERS	:	float x - the x coordinate
				float y - the y coordinate
				SpriteSheet* anim[4] - animation spritesheet
RETURNS		:	void
*/
Enemy::Enemy(float x, float y, SpriteSheet* anim[4]) {
	this->x = x;
	this->y = y;
	for (int i = 0; i < 4; i++) {
		this->anim[i] = anim[i];
	}
}

/*
METHOD		:	DrawAnim
DESCRIPTION	:	This method draws the animated sprite.
PARAMETERS	:	void
RETURNS		:	void
*/
void Enemy::DrawAnim() {
	anim[animSprite]->Draw(x, y);
}

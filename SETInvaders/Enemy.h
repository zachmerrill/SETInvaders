/*
FILE		:	Enemy.h
PROJECT		:	Graphics, Animation, & Sound - Assignment 1
DATE		:	February 13, 2018
AUTHOR		:	Zach Merrill
*/
#pragma once
#include "Entity.h"

/*
NAME		:	Enemy
DESCRIPTION	:	The Enemy class defines an enemy object's properties extended off of an entity.
*/
class Enemy : public Entity {
private:
	SpriteSheet* anim[4];

public:
	int animSprite = 0;

	Enemy(float x, float y, SpriteSheet* anim[4]);
	void DrawAnim();
};
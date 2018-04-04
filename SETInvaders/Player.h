/*
FILE		:	Player.h
PROJECT		:	Graphics, Animation, and Sound - Assignment 2
DATE		:	March 23, 2018
AUTHOR		:	Zach Merrill
*/
#pragma once
#include "Entity.h"

/*
NAME		:	Player
DESCRIPTION	:	This Player class defines a player turret. It is similar to other entities but will have
				be able to shoot toward a target enemy.
*/
class Player : public Entity {
public:
	Player(float x, float y, SpriteSheet* sprites);
	void DrawSpritesRotated(float x, float y);
};
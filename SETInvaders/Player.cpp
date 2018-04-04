/*
FILE		:	Player.cpp
PROJECT		:	Graphics, Animation, and Sound - Assignment 2
DATE		:	March 23, 2018
AUTHOR		:	Zach Merrill
DESCRIPTION	:	This file contains the methods for the the player object.
*/
#include "Player.h"

/*
METHOD		:	Player - Constructor
DESCRIPTION	:	This method creates a Player object and defines its attributes.
PARAMETERS	:	float x - target x coordinate
				float y - target y coordinate
				SpriteSheet* sprites - spritesheet for player
RETURNS		:	void
*/
Player::Player(float x, float y, SpriteSheet* sprites) {
	this->x = x;
	this->y = y;
	this->sprites = sprites;
}

/*
METHOD		:	DrawSpritesRotated
DESCRIPTION	:	This method draws the entity's spritesheet rotated.
PARAMETERS	:	float x - target x coordinate
					float y - target y coordinate
RETURNS		:	void
*/
void Player::DrawSpritesRotated(float x, float y) {
	if (sprites != NULL) {
		sprites->DrawRotated(this->x, this->y, x, y);
	}
}
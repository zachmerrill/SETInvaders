/*
FILE		:	Scene.h
PROJECT		:	Graphics, Animation, & Sound - Assignment 1
DATE		:	February 13, 2018
AUTHOR		:	Zach Merrill
*/
#pragma once

#include "Graphics.h"
#include "SpriteSheet.h"

/*
CLASS		:	Scene
DESCRIPTION	:	This class holds the basic requirements of a Scene or Level within the program.
					All other Scenes inherit from this one.
 */
class Scene {
protected:
	static Graphics* gfx; // Graphics object

public:
	/*
	METHOD		:	Init
	DESCRIPTION	:	This method initializes the Scene and graphics for it.
	PARAMETERS	:	Graphics* graphics - a pointer to graphics
	RETURNS		:	void
	*/
	static void Init(Graphics* graphics) {
		gfx = graphics;
	}

	virtual void Load() = 0;
	virtual void Unload() = 0;
	virtual void Update(float timeTotal, float deltaTime) = 0;
	virtual void Render() = 0;
};
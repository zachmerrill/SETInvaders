/*
FILE		:	TitleScene.h
PROJECT		:	Graphics, Animation, & Sound - Assignment 1
DATE		:	February 13, 2018
AUTHOR		:	Zach Merrill
*/
#pragma once
#include "Scene.h"

/*
NAME		:	Scene1
DESCRIPTION	:	The Scene1 class extends the Scene class to the specific needs of the level.
This particular scene contains 3 planet objects and an enemy. The 3 planets are
randomly placed within a grid which the enemy traverses downward through.
*/
class TitleScene : public Scene {
private:
	SpriteSheet * background;
	float width;
	float height;

public:
	void Load() override;
	void Unload() override;
	void Update(float timeTotal, float timeDelta) override;
	void Render() override;

};

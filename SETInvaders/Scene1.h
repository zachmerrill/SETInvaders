/*
FILE		:	Scene1.h
PROJECT		:	Graphics, Animation, & Sound - Assignment 1
DATE		:	February 13, 2018
AUTHOR		:	Zach Merrill
*/
#pragma once
#include "Scene.h"
#include "Enemy.h"
#include "Planet.h"
#include "Player.h"
#define COLUMNS 10
#define ROWS 10
#define SAFE_ROWS 4

/*
NAME		:	Scene1
DESCRIPTION	:	The Scene1 class extends the Scene class to the specific needs of the level.
				This particular scene contains 3 planet objects and an enemy. The 3 planets are
				randomly placed within a grid which the enemy traverses downward through.
*/
class Scene1 : public Scene {
private:
	float width; // Width of the screen
	float height; // Height of the screen
	float cellWidth; // Width of a cell
	float cellHeight; // Height of a cell
	float timeToUpdate = 0.5f; // Increment at which the scene updates
	Enemy* enemy; // Enemy ship
	Player* player; // Player ship
	Planet* planet1;
	Planet* planet2;
	Planet* planet3;
	SpriteSheet* background;
	bool forward = true; // Direction of enemy movement
	float occupied[3][2]; // Number of occupied squares
	bool gameOver = false;

public:
	void Load() override;
	void Unload() override;
	void Update(float timeTotal, float timeDelta) override;
	void Render() override;
	void Scene1::RandomizePlanet(Planet* planet);
	bool Scene1::SharedCell(int x1, int y1, int x2, int y2);

};

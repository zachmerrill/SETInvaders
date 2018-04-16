/*
 * FILE			:	Scene1.cpp
 * PROJECT		:	Graphics, Animation, & Sound - Assignment 1
 * DATE			:	February 13, 2018
 * AUTHOR		:	Zach Merrill
 * DESCRIPTION	:	This file contains the Scene1. This scene has 3 planets randomly placed and a player randomly placed. An enemy
					spaceship flies from left to right until reaching the bottom of the screen.
 */

#include "Game.h"
#include "Graphics.h"
#include "Scene1.h"
#include <time.h>

 /*
  * METHOD		:	Load()
  * DESCRIPTION	:	This method initializes all variables and pointers used within the scene.
  * PARAMETERS	:	void
  * RETURNS		:	void
  */
void Scene1::Load() {
	srand(time(NULL));

	// Get rendertarget dimensions for grid
	width = gfx->GetRenderTarget()->GetSize().width;
	height = gfx->GetRenderTarget()->GetSize().height;
	cellWidth = width / COLUMNS;
	cellHeight = height / ROWS;
	forward = true; // Direction of enemy movement
	gameOver = false;

	// Create objects
	// Enemy Alien
	SpriteSheet* enemyAnim[4] = {
		new SpriteSheet(L"./Assets/A2En1.png", gfx, SpriteSheet::CHROMA_COLOUR::NONE, 0.5f, 0.5f),
		new SpriteSheet(L"./Assets/A2En2.png", gfx, SpriteSheet::CHROMA_COLOUR::NONE, 0.5f, 0.5f),
		new SpriteSheet(L"./Assets/A2En3.png", gfx, SpriteSheet::CHROMA_COLOUR::NONE, 0.5f, 0.5f),
		new SpriteSheet(L"./Assets/A2En4.png", gfx, SpriteSheet::CHROMA_COLOUR::NONE, 0.5f, 0.5f),
	};
	enemy = new Enemy(
		(cellWidth / COLUMNS - 4) + (cellWidth / 4),
		(cellHeight / 6),
		enemyAnim);

	// Player DSAT
	player = new Player(
		(rand() % COLUMNS) * cellWidth + (cellWidth / 4),
		((rand() % 3) + 7) * cellHeight + (cellHeight / 5),
		new SpriteSheet(L"./Assets/DSAT.bmp", gfx, SpriteSheet::CHROMA_COLOUR::GREEN, 0.5f, 0.5f));

	// Planet 1
	planet1 = new Planet(
		0.0f, 0.0f,
		new SpriteSheet(L"./Assets/Planet1.bmp", gfx, SpriteSheet::CHROMA_COLOUR::GREEN, 0.5f, 0.5f));
	// Planet 2
	planet2 = new Planet(
		0.0f, 0.0f,
		new SpriteSheet(L"./Assets/Planet2.bmp", gfx, SpriteSheet::CHROMA_COLOUR::GREEN, 0.5f, 0.5f));
	// Planet 3
	planet3 = new Planet(
		0.0f, 0.0f,
		new SpriteSheet(L"./Assets/Planet3.bmp", gfx, SpriteSheet::CHROMA_COLOUR::GREEN, 0.5f, 0.5f));

	// Background Sector Image
	background = new SpriteSheet(L"./Assets/SectorBackground.bmp", gfx, SpriteSheet::CHROMA_COLOUR::NONE, 1.0f, 1.0f);

	// Randomly place planets
	memset(occupied, 0, sizeof(occupied[0][0]) * 3 * 2);
	RandomizePlanet(planet1);
	RandomizePlanet(planet2);
	RandomizePlanet(planet3);
}

/*
 * METHOD		:	Unload()
 * DESCRIPTION	:	This method deletes all objects to free up memory.
 * PARAMETERS	:	void
 * RETURNS		:	void
 */
void Scene1::Unload() {
	delete planet1;
	delete planet2;
	delete planet3;
	delete enemy;
	delete background;
}

/*
 * METHOD		:	Update()
 * DESCRIPTION	:	This method updates variables within the scene to create interactivity before rendering.
 * PARAMETERS	:	void
 * RETURNS		:	void
*/
void Scene1::Update(float timeTotal, float deltaTime) {
	// Determine if enemy has reached bottom of screen or not
	if (enemy->y >= height) {
		gameOver = true;
	}

	if (!gameOver) {
		// Determine direction of enemy
		if (forward) {
			if (enemy->x > (width - cellWidth)) { // If enemy is all the way right
				enemy->y += cellHeight; // Move down
				forward = false; // Left
			} else {
				enemy->x += cellWidth * deltaTime * 2; // Otherwise go right
			}
		} else {
			if (enemy->x < (cellWidth / 2)) { // If enemy is all the way left
				enemy->y += cellHeight; // Move down
				forward = true; // Right
			} else {
				enemy->x -= cellWidth * deltaTime * 2; // Otherwise go left
			}
		}
		if (timeTotal >= timeToUpdate) {

			// Enemy animation controller, updates frame with each tick
			if (enemy->animSprite < 3) {
				enemy->animSprite++;
			} else {
				enemy->animSprite = 0;
			}

			timeToUpdate = timeTotal + 0.5f;
		}
	} else {
		if (GetAsyncKeyState(VK_SPACE)) {
			Unload();
			Load();
		}
	}


}

/*
 * METHOD		:	RandomPlanet
 * DESCRIPTION	:	This method randomizes a planet location in the theoretical grid.
 * PARAMETERS	:	Planet* planet - pointer to a planet to be moved
 * RETURNS		:	void
 */
void Scene1::RandomizePlanet(Planet* planet) {
	float x = (rand() % COLUMNS) * cellWidth + (cellWidth / 4);
	float y = ((rand() % (ROWS - SAFE_ROWS)) + SAFE_ROWS) * cellHeight + (cellHeight / 5);
	int i = 0;
	for (i = 0; i < 3; i++) {
		// Ensure space is not occupied
		if (!SharedCell(occupied[i][0], occupied[i][1], x, y)) {
			occupied[i][0] = x;
			planet->x = x;
			occupied[i][1] = y;
			planet->y = y;
			// If at the end of the planet list
			// and all are occupied
			if (i == 2) {
				memset(occupied, 0, sizeof(occupied[0][0]) * 3 * 2); // Reset occupied list
				break;
			}
			break;
		}

		// If trying to place a planet
		// but all locations are taken
		if (i == 2) {
			// Recursively call again
			RandomizePlanet(planet);
		}
	}
}

/*
 * METHOD		:	SharedCell()
 * DESCRIPTION	:	This method checks if a cell in the grid is shared or free.
 * PARAMETERS	:	float x1 - first x coordinate
					float y1 - first y coordinate
					float x2 - second x coordinate
					float y2 - second y coordinate
 * RETURNS		:	bool - pass or fail
*/
bool Scene1::SharedCell(int x1, int y1, int x2, int y2) {
	bool shared = false;
	if ((x1 == x2) && (y1 == y2)) {
		shared = true;
	}
	return shared;
}

/*
 * METHOD		:	Render
 * DESCRIPTION	:	This method clears the screen and renders objects to the rendertarget.
 * PARAMETERS	:	void
 * RETURNS		:	void
*/
void Scene1::Render() {
	gfx->ClearScreen(0.0f, 0.0f, 0.0f);
	background->Draw(0.0f, 0.0f);
	planet1->DrawSprites();
	planet2->DrawSprites();
	planet3->DrawSprites();
	enemy->DrawAnim();
	if (enemy->y > (player->y - (cellHeight * 5))) {
		player->DrawSpritesRotated(enemy->x, enemy->y);
	} else {
		player->DrawSprites();
	}

	if (gameOver) {
		gfx->WriteText(L"Game Over!", width / 3.5, 300.0, 72.0, 255.0, 0.0, 0.0, 1.0);
		gfx->WriteText(L"Press Space to Restart", width / 3.15, 400.0, 32.0, 255.0, 0.0, 0.0, 1.0);
	}
}

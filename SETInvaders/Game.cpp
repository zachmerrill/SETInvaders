/*
FILE		:	Game.cpp
PROJECT		:	Graphics, Animation, & Sound - Assignment 1
DATE		:	February 13, 2018
AUTHOR		:	Zach Merrill
DESCRIPTION	:	This file contains the methods for the Game class.
*/
#include "Game.h"

Scene* Game::currentScene;
bool Game::Loading;
HPTimer* Game::hpTimer;

/*
METHOD		:	Init
DESCRIPTION	:	This method initializes the Game controller without a scene.
PARAMETERS	:	void
RETURNS		:	void
*/
void Game::Init() {
	Loading = true;
	currentScene = 0;
	hpTimer = new HPTimer();
}

/*
METHOD		:	LoadInitialScene
DESCRIPTION	:	This method loads the initial scene into the game controller.
PARAMETERS	:	Scene* sce - a pointer to the scene to load.
RETURNS		:	void
*/ 
void Game::LoadInitialScene(Scene* lev) {
	Loading = true; // This can help us avoid loading activity while rendering
	currentScene = lev;
	currentScene->Load();
	Loading = false;
}

/*
METHOD		:	SwitchScene
DESCRIPTION	:	This method  switches the game to a new scene and unloads the old scene.
PARAMETERS	:	Scene* sce - a pointer to the new scene.
RETURNS		:	void
*/
void Game::SwitchScene(Scene* lev) {
	Loading = true;
	currentScene->Unload();
	lev->Load();
	delete currentScene;
	currentScene = lev;
	Loading = false;
}

/*
METHOD		:	Render
DESCRIPTION	:	This method renders the current scene if the program is not currently loading.
PARAMETERS	:	void
RETURNS		:	void
*/
void Game::Render() {
	if(Loading) return;// Do not update or render if the scene is loading.
	currentScene->Render();
}

/*
METHOD		:	Update
DESCRIPTION	:	This method updates the current scene if the program is not currently loading.
PARAMETERS	:	void
RETURNS		:	void
*/
void Game::Update() {
	if (Loading) return;
	hpTimer->Update();
	currentScene->Update(hpTimer->GetTimeTotal(), hpTimer->GetDeltaTime());
}

Scene* Game::GetCurrentScene() {
	return currentScene;
}
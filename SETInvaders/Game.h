/*
FILE		:	Game.h
PROJECT		:	Graphics, Animation, & Sound - Assignment 1
DATE		:	February 13, 2018
AUTHOR		:	Zach Merrill
*/
#pragma once

#include "Scene.h"
#include "Graphics.h"
#include "HPTimer.h"

/*
NAME		:	Game
DESCRIPTION	:	The Game class controls the functions of the game program. It holds the current scene
				and the methods to load, initialize, render, and update that scene.
*/
class Game {
	Game() {}
	static Scene* currentScene;
	static HPTimer* hpTimer;
public:
	static bool Loading;
	static void Init();
	static void LoadInitialScene(Scene* lev);
	static void SwitchScene(Scene* lev);
	static void Render();
	static void Update();
	static Scene* GetCurrentScene();
};
/*
* FILE			:	TitleScene.cpp
* PROJECT		:	Graphics, Animation, & Sound - Assignment 3
* DATE			:	April 7, 2018
* AUTHOR		:	Zach Merrill
* DESCRIPTION	:	This scene is the title screen of SET Invaders and waits until
					the enter button is pressed to progress.
*/

#include "Game.h"
#include "Graphics.h"
#include "TitleScene.h"

/*
* METHOD		:	Load()
* DESCRIPTION	:	This method initializes all variables and pointers used within the scene.
* PARAMETERS	:	void
* RETURNS		:	void
*/
void TitleScene::Load() {
	background = new SpriteSheet(L"./Assets/TitleBackground.bmp", gfx, SpriteSheet::CHROMA_COLOUR::NONE, 1.0f, 1.0f);
	width = gfx->GetRenderTarget()->GetSize().width;
	height = gfx->GetRenderTarget()->GetSize().height;
}

/*
* METHOD		:	Unload()
* DESCRIPTION	:	This method deletes all objects to free up memory.
* PARAMETERS	:	void
* RETURNS		:	void
*/
void TitleScene::Unload() {
	delete background;
}

/*
* METHOD		:	Update()
* DESCRIPTION	:	This method updates variables within the scene to create interactivity before rendering.
* PARAMETERS	:	void
* RETURNS		:	void
*/
void TitleScene::Update(float timeTotal, float deltaTime) {


}

/*
* METHOD		:	Render
* DESCRIPTION	:	This method clears the screen and renders objects to the rendertarget.
* PARAMETERS	:	void
* RETURNS		:	void
*/
void TitleScene::Render() {
	gfx->ClearScreen(0.0f, 0.0f, 0.0f);
	background->Draw(0.0f, 0.0f);
	gfx->WriteText(L"Welcome to SET Invaders!", width / 5, 100.0, 48.0, 255.0, 255.0, 0.0, 1.0);
	gfx->WriteText(L"Press Space to Begin", width / 3, 500.0, 32.0, 255.0, 255.0, 255.0, 1.0);

}

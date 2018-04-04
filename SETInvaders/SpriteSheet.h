/*
FILE		:	SpriteSheet.h
PROJECT		:	Graphics, Animation, & Sound - Assignment 1
DATE		:	February 13, 2018
AUTHOR		:	Zach Merrill
*/
#pragma once

#include <wincodec.h> // This is the WIC codec header - we need this to decode image files
#include <math.h>
#include "Graphics.h" // This includes both Windows and D2D libraries
#define PI 3.14159265

/*
NAME		:	SpriteSheet
DESCRIPTION	:	The SpriteSheet class handles Bitmap rendering within the program. It contains
				a pointer to a graphics object and a bitmap object and has methods for rendering
				a bitmap to the screen.
*/
class SpriteSheet {
	Graphics* gfx; // Reference to the Graphics class
	ID2D1Bitmap* bmp; // This will hold our loaded and converted Bitmap file
	ID2D1Effect* bmpEffect;

public:
	enum CHROMA_COLOUR {
		NONE,
		RED,
		GREEN,
		BLUE
	};

	// Constructor
	SpriteSheet(wchar_t* filename, Graphics* gfx, CHROMA_COLOUR colour, float scaleX, float scaleY);

	// Destructor
	~SpriteSheet();

	// Draw bitmap to the render target
	void Draw(float x, float y);
	void DrawRotated(float x1, float y1, float x2, float y2);

};
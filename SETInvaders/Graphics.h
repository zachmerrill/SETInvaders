/*
FILE		:	Graphics.h
PROJECT		:	Graphics, Animation, & Sound - Assignment 1
DATE		:	February 13, 2018
AUTHOR		:	Zach Merrill
*/
#pragma once
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "Dwrite.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "windowscodecs.lib")
#pragma comment(lib, "d2d1.lib")

#include<Windows.h>
#include <d2d1_1.h>
#include <d2d1.h>
#include <d3d11_1.h>
#include <d2d1effects.h>
#include <d2d1effects_2.h>
#include <d2d1effecthelpers.h>

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768

/*
NAME		:	Graphics
DESCRIPTION	:	The intent of the Graphics class is to handle our DirectX calls, and to be largely responsible
				for managing the rendertarget.
*/
class Graphics {
	ID2D1Factory * factory; // Reference to the factory
	ID2D1HwndRenderTarget* rendertarget; // Reference to the render target (screen)
	ID2D1SolidColorBrush* brush; // Reference to the brush
	ID2D1GeometrySink *sink; // Reference to the sink

public:
	Graphics(); // Constructor

	~Graphics(); // Destructor

	// Initialization methods
	bool Init(HWND windowHandle);

	ID2D1RenderTarget* GetRenderTarget() {
		return rendertarget;
	}

	ID2D1DeviceContext* GetDeviceContext() {
		ID2D1DeviceContext *rtDC;
		rendertarget->QueryInterface(&rtDC);
		return rtDC;
	}

	void BeginDraw() { rendertarget->BeginDraw(); }
	void EndDraw() { rendertarget->EndDraw(); }

	// Draw methods
	void ClearScreen(float r, float g, float b);
	void DrawCircle(float c, float y, float radius, float r, float g, float b, float a);
	void DrawEqTriangle(float x, float y, float sidelength, float r, float g, float b, float a);
	void DrawLine(float x1, float y1, float x2, float y2, float r, float g, float b, float a);
};

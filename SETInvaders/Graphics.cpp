/*
FILE		:	Graphics.cpp
PROJECT		:	Graphics, Animation, & Sound - Assignment 1
DATE		:	February 13, 2018
AUTHOR		:	Zach Merrill
DESCRIPTION	:	This file contains the methods for the Graphics class.
*/

#include "Graphics.h"

/*
METHOD		:	Graphics - Constructor
DESCRIPTION	:	This method creates a Graphics object and defaults the values.
PARAMETERS	:	void
RETURNS		:	void
*/
Graphics::Graphics() {
	factory = NULL;
	rendertarget = NULL;
	brush = NULL;
}

/*
METHOD		:	~Graphics - Destructor
DESCRIPTION	:	This method releases all COM objects on deletion of the graphics object.
PARAMETERS	:	void
RETURNS		:	void
*/
Graphics::~Graphics() {
	if(factory) factory->Release();
	if(rendertarget) rendertarget->Release();
	if(brush) brush->Release();
}

/*
METHOD		:	Init
DESCRIPTION	:	This method initializes the rendertarget when given a window handle.
PARAMETERS	:	HWND windowHandle - the window's handle to initialize.
RETURNS		:	bool - pass or fail.
*/
bool Graphics::Init(HWND windowHandle) {
	HRESULT res = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory);
	if(res != S_OK) return false;

	RECT rect;
	GetClientRect(windowHandle, &rect); //set the rect's right and bottom properties = the client window's size

	res = factory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(windowHandle, D2D1::SizeU(rect.right, rect.bottom)),
		&rendertarget);
	if(res != S_OK) return false;

	res = rendertarget->CreateSolidColorBrush(D2D1::ColorF(0, 0, 0, 0), &brush);
	if(res != S_OK) return false;
	return true;
}

/*
METHOD		:	ClearScreen
DESCRIPTION	:	This method clears the rendertarget of all drawn objects.
PARAMETERS	:	float r - red
				float g - green
				float b - blue
RETURNS		:	void
*/
void Graphics::ClearScreen(float r, float g, float b) {
	rendertarget->Clear(D2D1::ColorF(r, g, b));
}


/*
METHOD		:	DrawCircle
DESCRIPTION	:	This method draws a circle in the render target.
PARAMETERS	:	float x - x coordinate
				float y - y coordinate
				float radius - circle radius
				float r - red
				float g - green
				float b - blue
				float a - alpha
RETURNS		:	void
*/
void Graphics::DrawCircle(float x, float y, float radius, float r, float g, float b, float a) {
	brush->SetColor(D2D1::ColorF(r, g, b, a));
	rendertarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius), brush, 3.0f);
}

/*
METHOD		:	DrawEqTriangle
DESCRIPTION	:	This method draws an equilateral triangle in the render target.
PARAMETERS	:	float x - x coordinate
				float y - y coordinate
				float sidelength - triangle sidelength
				float r - red
				float g - green
				float b - blue
				float a - alpha
RETURNS		:	void
*/
void Graphics::DrawEqTriangle(float x, float y, float sidelength, float r, float g, float b, float a) {
	brush->SetColor(D2D1::ColorF(r, g, b, a));
	ID2D1PathGeometry *triangleGeometry;

	factory->CreatePathGeometry(&triangleGeometry);
	triangleGeometry->Open(&sink);

	sink->SetFillMode(D2D1_FILL_MODE_WINDING);

	sink->BeginFigure(
		D2D1::Point2F(x, y),
		D2D1_FIGURE_BEGIN_FILLED
	);
	D2D1_POINT_2F points[3] = {
		D2D1::Point2F(x, y),
		D2D1::Point2F(x + sidelength, y),
		D2D1::Point2F(x + (sidelength / 2), y + sidelength),
	};
	sink->AddLines(points, ARRAYSIZE(points));
	sink->EndFigure(D2D1_FIGURE_END_CLOSED);
	sink->Close();
	rendertarget->FillGeometry(triangleGeometry, brush);
}

/*
METHOD		:	DrawLine
DESCRIPTION	:	This method draws a line in the render target.
PARAMETERS	:	float x1 - starting x coordinate
				float y1 - starting y coordinate
				float x2 - ending x coordinate
				float y2 - ending y coordinate
				float r - red
				float g - green
				float b - blue
				float a - alpha
RETURNS		:	void
*/
void Graphics::DrawLine(float x1, float y1, float x2, float y2, float r, float g, float b, float a) {
	brush->SetColor(D2D1::ColorF(r, g, b, a));
	rendertarget->DrawLine(D2D1::Point2F(x1, y1), D2D1::Point2F(x2, y2), brush, 1.0f, NULL);
}
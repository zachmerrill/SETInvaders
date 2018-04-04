/*
FILE		:	main.cpp
PROJECT		:	Graphics, Animation, & Sound - Assignment 1
DATE		:	February 13, 2018
AUTHOR		:	Zach Merrill
DESCRIPTION	:	This file is the main entry point into the program. It holds the game loop which handles messages
				and handles the graphics object rendering.
*/
#include <Windows.h>
#include "Graphics.h"
#include "Scene1.h"
#include "Game.h"


Graphics* graphics;

/*
METHOD	:	WindowProc
DESCRIPTION	:	This function handles the messages sent to the Win32 application window.
PARAMETERS	:	HWND hwnd - A handle to the window
				UINT uMsg - The message
				WPARAM wParam -	Message parameter
				LPARAM lParam - Message parameter
RETURNS		:	LRESULT - The result of window processing
*/
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	if (uMsg == WM_DESTROY) {
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

/*
METHOD	:	wWinMain
DESCRIPTION	:	This function is the entry point for the application.
PARAMETERS	:	HINSTANCE hInstance - The handle to the instance
				HINSTANCE prevInstance - Unimportant, always 0
				LPWSTR cmd - Command line arguments
				int nCmdShow - flag for minimized, maximized, or normal
RETURNS		:	int - result of program
*/
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPWSTR cmd, int nCmdShow) {
	//Set up window for directx
	WNDCLASSEX windowclass;
	ZeroMemory(&windowclass, sizeof(WNDCLASSEX));
	windowclass.cbSize = sizeof(WNDCLASSEX);
	windowclass.hbrBackground = (HBRUSH) COLOR_WINDOW;
	windowclass.hInstance = hInstance;
	windowclass.lpfnWndProc = WindowProc;
	windowclass.lpszClassName = "MainWindow";
	windowclass.style = CS_HREDRAW | CS_VREDRAW; // Redraw window if size adjustment is made

	RegisterClassEx(&windowclass);

	// Create window rect
	RECT rect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
	AdjustWindowRectEx(&rect, WS_OVERLAPPED, false, WS_EX_OVERLAPPEDWINDOW);

	// Set up window handle with position, name, and size based on rect
	HWND windowhandle = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, "MainWindow", "SET Invaders", WS_OVERLAPPEDWINDOW, 100, 100,
		rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, hInstance, 0);
	if (!windowhandle) {
		return -1;
	}

	// Initialize window
	graphics = new Graphics();
	if(!graphics->Init(windowhandle)) {
		delete graphics;
		return -1;
	}

	// Initialize graphics object and load main scene
	Scene::Init(graphics);
	ShowWindow(windowhandle, nCmdShow);
	Game::Init();
	Game::LoadInitialScene(new Scene1());

	// Game infinite loop
#pragma region GameLoop

	// Use a PeekMessage to avoid locking the graphics/windoProc
	MSG message;
	message.message = WM_NULL;
	while(message.message != WM_QUIT) {
		if(PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
			// Send a message to the WindowProc IF there is one
			DispatchMessage(&message);
		else {
			// Update game
			Game::Update();

			//Render game graphics
			graphics->BeginDraw();
			Game::Render();
			graphics->EndDraw();

		}
	}

#pragma endregion
	delete graphics;
	return 0;
}
#pragma once
#include <string>
#include <sstream>
#include <math.h>
#include "WindowDefinitions.h"
#include "KeyboardControls.h"
#include "Mouse.h"

class Window
{
public:

	Window(HINSTANCE hInstance);

	void Update(float dt);


	Vector2D GetWindowCenter();
	bool InitializeWindow();

	void SetWindowTitle(LPCWSTR lpString);
	void SetFrameStats(float framesPS, float milisecondsPF);


	bool BoolMouseInWindow(Mouse* mouse);
	void BindMouseToWindow(Mouse* mouse);

	HWND GetHandle();
	std::wstring GetApplicationTitle();
	bool DisplayWindow();
	
	LRESULT MessageProc(HWND, UINT, WPARAM, LPARAM);

	~Window();
private:

	RECT *window;

	HINSTANCE hInstance;
	std::wstring applicationTitle;
	LPCSTR windowClassName;
	DWORD windowStyle;
	HWND hWindow;
};


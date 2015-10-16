#pragma once
#include <string>
#include <sstream>
#include "WindowDefinitions.h"
#include "KeyboardControls.h"

class Window
{
public:

	Window(HINSTANCE hInstance);

	void Update(float dt);

	bool InitializeWindow();
	void SetWindowTitle(LPCWSTR lpString);
	void SetFrameStats(float framesPS, float milisecondsPF);
	HWND GetHandle();
	std::wstring GetApplicationTitle();
	bool DisplayWindow();

	LRESULT MessageProc(HWND, UINT, WPARAM, LPARAM);

	~Window();
private:

	RECT *window;
	POINT *mouse;

	HINSTANCE hInstance;
	std::wstring applicationTitle;
	LPCSTR windowClassName;
	DWORD windowStyle;
	HWND hWindow;
};


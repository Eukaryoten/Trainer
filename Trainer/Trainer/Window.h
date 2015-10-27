#pragma once
#include <string>
#include <sstream>
#include <math.h>
#include "WindowDefinitions.h"
#include "KeyboardControls.h"

class Window
{
public:

	Window(HINSTANCE hInstance);

	void Update(float dt);


	Vector2 GetWindowCenter();
	bool InitializeWindow();

	void SetWindowTitle(LPCWSTR lpString);
	void SetFrameStats(float framesPS, float milisecondsPF);
	void SetMouseOutsideWindow(bool);
	void SetMousePosition(int x, int y);

	HWND GetHandle();
	std::wstring GetApplicationTitle();
	bool DisplayWindow();
	bool MouseInWindow();

	void KeepMouseInWindow();

	bool MouseRegisteredInWindow();
	bool MouseJustEnteredWindow();

	Vector2 GetMousePosition();
	float GetDeltaMouseDistance();
	void CenterMouseToWindow();


	LRESULT MessageProc(HWND, UINT, WPARAM, LPARAM);

	~Window();
private:

	RECT *window;

	POINT *currentMousePosition;
	POINT *lastMousePosition;

	bool bMouseOutside;

	HINSTANCE hInstance;
	std::wstring applicationTitle;
	LPCSTR windowClassName;
	DWORD windowStyle;
	HWND hWindow;
};


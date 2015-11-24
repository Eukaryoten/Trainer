#pragma once
#include <string>
#include <sstream>
#include <math.h>
#include "WindowDefinitions.h"
#include "StandardKeyboard.h"
#include "MouseObject.h"

class WindowObject
{
public:

	WindowObject(HINSTANCE hInstance);

	void Update(float dt);


	Vector2D GetWindowObjectCenter();
	bool InitializeWindowObject();

	void SetWindowObjectTitle(LPCWSTR lpString);
	void SetFrameStats(float framesPS, float milisecondsPF);


	bool BoolMouseObjectInWindowObject(MouseObject* MouseObject);
	void BindMouseObjectToWindowObject(MouseObject* MouseObject);

	HWND GetHandle();
	std::wstring GetApplicationTitle();
	bool DisplayWindowObject();
	
	LRESULT MessageProc(HWND, UINT, WPARAM, LPARAM);

	~WindowObject();
private:

	RECT *window;

	HINSTANCE hInstance;
	std::wstring applicationTitle;
	LPCSTR windowClassName;
	DWORD windowStyle;
	HWND hWindow;
};


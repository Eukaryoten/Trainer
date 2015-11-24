#include "WindowObject.h"

namespace {

	WindowObject *pWind;

}

WindowObject::WindowObject(HINSTANCE hInstance){
	pWind = this;
	window = new RECT;
	hWindow = NULL;
	applicationTitle = L"Game Engine";
	windowStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
	windowClassName = "APPWINDOWCLASS";
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {

	return pWind->MessageProc(hWnd, msg, wParam, lParam); // This shit
}

bool WindowObject::InitializeWindowObject() {

	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance; // This not working, yellow arrow was on it last
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName = L"WindowClass";
	RegisterClassEx(&wc);

	hWindow = CreateWindowEx(NULL,
		L"WindowClass",    // name of the window class
		applicationTitle.c_str(),   // title of the window
		WS_OVERLAPPEDWINDOW,    // window style
		WINDOW_POSITIONX,    // x-position of the window
		WINDOW_POSITIONY,    // y-position of the window
		SCREEN_WIDTH,    // width of the window
		SCREEN_HEIGHT,    // height of the window
		NULL,    // we have no parent window, NULL
		NULL,    // we aren't using menus, NULL
		hInstance,    // application handle
		NULL);    // used with multiple windows, NULL

	if (!hWindow) {
		MessageBoxA(NULL, "Failed to create window", NULL, NULL);
		return false;
	}
}


bool WindowObject::BoolMouseObjectInWindowObject(MouseObject* MouseObject) {

	if (MouseObject->GetPosition().x <= window->right &&
		MouseObject->GetPosition().x >= window->left &&

		MouseObject->GetPosition().y >= window->top &&
		MouseObject->GetPosition().y <= window->bottom) return true;

	return false;
}


void WindowObject::BindMouseObjectToWindowObject(MouseObject* MouseObject) {

	if (MouseObject->GetPosition().x > window->right)  MouseObject->SetMouseObjectPosition(window->left, MouseObject->GetPosition().y);
	if (MouseObject->GetPosition().x < window->left)   MouseObject->SetMouseObjectPosition(window->right, MouseObject->GetPosition().y);
	if (MouseObject->GetPosition().y < window->top)    MouseObject->SetMouseObjectPosition(MouseObject->GetPosition().x, window->bottom);
	if (MouseObject->GetPosition().y > window->bottom) MouseObject->SetMouseObjectPosition(MouseObject->GetPosition().x, window->top);

}


void WindowObject::Update(float dt) {

	GetWindowRect(hWindow, window);
	
}

Vector2D WindowObject::GetWindowObjectCenter() {

	Vector2D center;

	center.x = (window->left) + SCREEN_WIDTH/2;
	center.y = (window->bottom) - SCREEN_HEIGHT/2;

	return center;
}



bool WindowObject::DisplayWindowObject() {

	ShowWindow(hWindow, SW_SHOW);

	return true;
}

void WindowObject::SetWindowObjectTitle(LPCWSTR lpString) {

	SetWindowText(hWindow, lpString);
}

void WindowObject::SetFrameStats(float framesPS, float milisecondsPF) {

	std::wostringstream outs;
	outs.precision(6);
	outs << applicationTitle << L"Game Engine "
		<< L"FPS: " << framesPS << L"    "
		<< L"Frame Time: " << milisecondsPF << L" (ms)";
	SetWindowText(hWindow, outs.str().c_str());

}


HWND WindowObject::GetHandle() {
	return hWindow;
}

std::wstring WindowObject::GetApplicationTitle() {
	return applicationTitle;
}

LRESULT WindowObject::MessageProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {

	static KeyboardObject* keyboard = (StandardKeyboard*)StandardKeyboard::GetInstance();

	switch (msg) // Check the message and then decide on what to do with message
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_KEYDOWN: // If message = WM_KEYDOWN
		if (wParam == VK_ESCAPE) DestroyWindow(hWnd); // Then check the additional wParam
		if (wParam == VK_LEFT  ) keyboard->SetLeftKey(true);
		if (wParam == VK_RIGHT ) keyboard->SetRightKey(true);
		if (wParam == VK_UP    ) keyboard->SetUpKey(true);
		if (wParam == VK_DOWN  ) keyboard->SetDownKey(true);

		if (wParam == VK_W) keyboard->SetWKey(true);
		if (wParam == VK_A) keyboard->SetAKey(true);
		if (wParam == VK_S) keyboard->SetSKey(true);
		if (wParam == VK_D) keyboard->SetDKey(true);
		return 0;
	case WM_KEYUP:
		if (wParam == VK_LEFT) keyboard->SetLeftKey(false);
		if (wParam == VK_RIGHT) keyboard->SetRightKey(false);
		if (wParam == VK_UP) keyboard->SetUpKey(false);
		if (wParam == VK_DOWN) keyboard->SetDownKey(false);

		if (wParam == VK_W) keyboard->SetWKey(false);
		if (wParam == VK_A) keyboard->SetAKey(false);
		if (wParam == VK_S) keyboard->SetSKey(false);
		if (wParam == VK_D) keyboard->SetDKey(false);
		return 0;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}


WindowObject::~WindowObject(){
}

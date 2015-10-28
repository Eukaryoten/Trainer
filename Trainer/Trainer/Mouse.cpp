#include "Mouse.h"



Mouse::Mouse(){

	currentPosition;
	lastPosition;
	positionTimer = 0;

	GetCursorPos(&currentPosition);
	lastPosition = currentPosition;
	
}

void Mouse::Update(float dt) {

	//positionTimer += dt;

	lastPosition = currentPosition;
	GetCursorPos(&currentPosition);
}

Vector2D Mouse::GetPosition() {

	Vector2D pos;

	GetCursorPos(&currentPosition);

	pos.x = currentPosition.x;
	pos.y = currentPosition.y;

	return pos;

}

Vector2D Mouse::GetDeltaMousePosition(float dt) {

	Vector2D deltaPosition;

	deltaPosition.x = (currentPosition.x - lastPosition.x);
	deltaPosition.y = (currentPosition.y - lastPosition.y);

	return deltaPosition;
}

bool Mouse::BoolMouseJustEnteredWindow() {
	return true;
}

bool Mouse::BoolMouseRegisteredInWindow() {
	return true;
}

void Mouse::CenterMouseToWindow() {

	//Vector2D center = GetWindowCenter();
	//SetCursorPos(center.x, center.y);

}

void Mouse::SetMouseOutsideWindow(bool mouse) {
}


void Mouse::SetMousePosition(int x, int y) {

	SetCursorPos(x, y);
}

Mouse::~Mouse()
{
}

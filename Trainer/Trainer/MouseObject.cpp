#include "MouseObject.h"



MouseObject::MouseObject(){

	currentPosition;
	lastPosition;
	positionTimerObject = 0;

	GetCursorPos(&currentPosition);
	lastPosition = currentPosition;
	
}

void MouseObject::Update(float dt) {

	//positionTimerObject += dt;

	lastPosition = currentPosition;
	GetCursorPos(&currentPosition);
}

Vector2D MouseObject::GetPosition() {

	Vector2D pos;

	GetCursorPos(&currentPosition);

	pos.x = currentPosition.x;
	pos.y = currentPosition.y;

	return pos;

}

Vector2D MouseObject::GetDeltaMouseObjectPosition(float dt) {

	Vector2D deltaPosition;

	deltaPosition.x = (currentPosition.x - lastPosition.x);
	deltaPosition.y = (currentPosition.y - lastPosition.y);

	return deltaPosition;
}

bool MouseObject::BoolMouseObjectJustEnteredWindowObject() {
	return true;
}

bool MouseObject::BoolMouseObjectRegisteredInWindowObject() {
	return true;
}

void MouseObject::CenterMouseObjectToWindowObject() {

	//Vector2D center = GetWindowObjectCenter();
	//SetCursorPos(center.x, center.y);

}

void MouseObject::SetMouseObjectOutsideWindowObject(bool MouseObject) {
}


void MouseObject::SetMouseObjectPosition(int x, int y) {

	SetCursorPos(x, y);
}

MouseObject::~MouseObject()
{
}

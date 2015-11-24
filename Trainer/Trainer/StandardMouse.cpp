#include "StandardMouse.h"



StandardMouse::StandardMouse(){

	GetCursorPos(&currentPosition);
	lastPosition = currentPosition;

	instance = this;
}

StandardMouse::StandardMouse(MouseObject* mouse) {

	GetCursorPos(&currentPosition);
	lastPosition = currentPosition;

	instance = mouse;
}

MouseObject* StandardMouse::GetInstance() {

	if (instance == NULL) {
		new StandardMouse();
	}
	return instance;
}


StandardMouse::~StandardMouse(){
}

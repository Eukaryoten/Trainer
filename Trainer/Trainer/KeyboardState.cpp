#include "KeyboardState.h"

bool KeyboardState::upKey;
bool KeyboardState::downKey;
bool KeyboardState::leftKey;
bool KeyboardState::rightKey;

bool KeyboardState::wKey;
bool KeyboardState::aKey;
bool KeyboardState::sKey;
bool KeyboardState::dKey;


void KeyboardState::SetUpKey(bool key) {
	upKey = key;
}
void KeyboardState::SetDownKey(bool key) {
	downKey = key;
}
void KeyboardState::SetLeftKey(bool key) {
	leftKey = key;
}
void KeyboardState::SetRightKey(bool key) {
	rightKey = key;
}

bool KeyboardState::GetUpKey() {
	return upKey;
}
bool KeyboardState::GetDownKey() {
	return downKey;
}
bool KeyboardState::GetLeftKey() {
	return leftKey;
}
bool KeyboardState::GetRightKey() {
	return rightKey;
}

void KeyboardState::SetWKey(bool key) {
	wKey = key;
}
void KeyboardState::SetAKey(bool key) {
	aKey = key;
}
void KeyboardState::SetSKey(bool key) {
	sKey = key;
}
void KeyboardState::SetDKey(bool key) {
	dKey = key;
}

bool KeyboardState::GetWKey() {
	return wKey;
}
bool KeyboardState::GetAKey() {
	return aKey;
}
bool KeyboardState::GetSKey() {
	return sKey;
}
bool KeyboardState::GetDKey() {
	return dKey;
}

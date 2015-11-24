#include "KeyboardObject.h"

KeyboardObject* KeyboardObject::instance = 0;

void KeyboardObject::SetUpKey(bool key) {
	upKey = key;
}
void KeyboardObject::SetDownKey(bool key) {
	downKey = key;
}
void KeyboardObject::SetLeftKey(bool key) {
	leftKey = key;
}
void KeyboardObject::SetRightKey(bool key) {
	rightKey = key;
}

bool KeyboardObject::GetUpKey() {
	return upKey;
}
bool KeyboardObject::GetDownKey() {
	return downKey;
}
bool KeyboardObject::GetLeftKey() {
	return leftKey;
}
bool KeyboardObject::GetRightKey() {
	return rightKey;
}

void KeyboardObject::SetWKey(bool key) {
	wKey = key;
}
void KeyboardObject::SetAKey(bool key) {
	aKey = key;
}
void KeyboardObject::SetSKey(bool key) {
	sKey = key;
}
void KeyboardObject::SetDKey(bool key) {
	dKey = key;
}

bool KeyboardObject::GetWKey() {
	return wKey;
}
bool KeyboardObject::GetAKey() {
	return aKey;
}
bool KeyboardObject::GetSKey() {
	return sKey;
}
bool KeyboardObject::GetDKey() {
	return dKey;
}


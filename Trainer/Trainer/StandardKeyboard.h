#pragma once
#include "KeyboardObject.h"
#include "WindowDefinitions.h"

class StandardKeyboard : public KeyboardObject
{
public:
	static KeyboardObject* GetInstance();
protected:
	StandardKeyboard();
	~StandardKeyboard();
};


#pragma once
#include <math.h>
#include "WindowDefinitions.h"

class MouseObject
{
public:
	MouseObject();

	void Update(float dt);

	void SetMouseObjectOutsideWindowObject(bool);
	void SetMouseObjectPosition(int x, int y);
	

	bool BoolMouseObjectRegisteredInWindowObject();
	bool BoolMouseObjectJustEnteredWindowObject();


	Vector2D GetPosition();
	Vector2D GetDeltaMouseObjectPosition(float dt);
	void CenterMouseObjectToWindowObject();

	~MouseObject();
private:

	float positionTimer;
	POINT currentPosition;
	POINT lastPosition;
};


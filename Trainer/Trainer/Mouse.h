#pragma once
#include <math.h>
#include "WindowDefinitions.h"

class Mouse
{
public:
	Mouse();

	void Update(float dt);

	void SetMouseOutsideWindow(bool);
	void SetMousePosition(int x, int y);
	

	bool BoolMouseRegisteredInWindow();
	bool BoolMouseJustEnteredWindow();


	Vector2D GetPosition();
	Vector2D GetDeltaMousePosition(float dt);
	void CenterMouseToWindow();

	~Mouse();
private:

	float positionTimer;
	POINT currentPosition;
	POINT lastPosition;
};


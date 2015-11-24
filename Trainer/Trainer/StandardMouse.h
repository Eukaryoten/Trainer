#pragma once
#include "MouseObject.h"

class StandardMouse : public MouseObject
{
public:
	static MouseObject* GetInstance();
protected:
	StandardMouse();
	StandardMouse(MouseObject* mouse);
	virtual ~StandardMouse();
};


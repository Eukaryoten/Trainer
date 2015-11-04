#pragma once
#include <time.h>
#include "Timer.h"
#include "WindowObject.h"
#include "MouseObject.h"
#include "Pipeline.h"


class Framework
{

public:
	Framework();
	Framework(HINSTANCE hInstance);

	bool Initialize();
	virtual bool InitializeGame();

	virtual void Update(float dt) = 0;
	virtual void Render() = 0;
	virtual void CleanD3D();

	int Run();
	void CalculateFrameStats();
	
	virtual ~Framework();
protected:

	WindowObject *window;
	MouseObject *mouse;


	Pipeline *pipeline;
	Timer* timer;
	WPARAM cWParam;
	LPARAM cLParam;
};



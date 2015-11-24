#pragma once
#include <time.h>
#include "TimerObject.h"
#include "WindowObject.h"
#include "StandardMouse.h"
#include "StandardKeyboard.h"
#include "PipelineObject.h"


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
	StandardMouse *mouse;
	StandardKeyboard *keyboard;


	PipelineObject *pipeline;
	TimerObject* timer;
	WPARAM cWParam;
	LPARAM cLParam;
};



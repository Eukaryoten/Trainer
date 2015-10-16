#pragma once

#include "Framework.h"

Framework::Framework(void){
}

Framework::Framework(HINSTANCE hInstance){

	window = new Window(hInstance);
	pipeline = new Pipeline();
	timer = new Timer();
}

int Framework::Run()
{
	MSG msg = { 0 };
	timer->Reset();

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			timer->Tick();
			CalculateFrameStats();
			Update(timer->DeltaTime());
			Render();
		}
	}

	return msg.wParam;
}

void Framework::CalculateFrameStats(){

	// Code computes the average frames per second, and also the 
	// average time it takes to render one frame.  These stats 
	// are appended to the window caption bar.

	static int frameCnt = 0;
	static float timeElapsed = 0.0f;

	frameCnt++;

	// Compute averages over one second period.
	if ((timer->TotalTime() - timeElapsed) >= 1.0f)
	{
		float fps = (float)frameCnt; // fps = frameCnt / 1
		float mspf = 1000.0f / fps;

		window->SetFrameStats(fps, mspf);

		// Reset for next average.
		frameCnt = 0;
		timeElapsed += 1.0f;
	}
}

bool Framework::Initialize(){

	if (!window->InitializeWindow()) return false;
	if (!pipeline->InitializeWindowSettings(window->GetHandle())) return false;
	if (!window->DisplayWindow()) return false;
	if (!pipeline->InitializeDirect3D()) return false;
	if (!InitializeGame()) return false;
	return true;
}
bool Framework::InitializeGame(){
	return true;
}
void Framework::CleanD3D(){
}
Framework::~Framework(void){
}


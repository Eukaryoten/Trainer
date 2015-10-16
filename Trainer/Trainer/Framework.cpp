#pragma once

#include "Framework.h"

Framework::Framework(void){
}

Framework::Framework(HINSTANCE hInstance){
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
	//if (!InitializeD3D(window->GetHandle())) return false;
	if (!window->DisplayWindow()) return false;
	if (!InitializeGame()) return false;
	return true;
}

bool Framework::InitializeD3D(HWND hWindow) {

	/*DXGI_MODE_DESC bufferDesc;

	ZeroMemory(&bufferDesc, sizeof(DXGI_MODE_DESC));

	bufferDesc.Width = SCREEN_WIDTH;
	bufferDesc.Height = SCREEN_HEIGHT;
	bufferDesc.RefreshRate.Numerator = 60;
	bufferDesc.RefreshRate.Denominator = 1;
	bufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	bufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	bufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));

	swapChainDesc.BufferDesc = bufferDesc;
	swapChainDesc.SampleDesc.Count = 1;                               // How many multisamples
	swapChainDesc.SampleDesc.Quality = 0;                             // Multisample quality level
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;      // How swap chain is to be used
	swapChainDesc.BufferCount = 1;                                    // One back buffer
	swapChainDesc.OutputWindow = hWindow;                                // the window to be used
	swapChainDesc.Windowed = TRUE;                                    // windowed/full-screen mode
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;


	// Create Device and Swap Chain using struct information

	D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, NULL, NULL, NULL,
		D3D11_SDK_VERSION, &swapChainDesc, &swapChain, &dev, NULL, &devCon);

	// Get the address of the back buffer

	ID3D11Texture2D *pBackBuffer;
	swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

	// Use the back buffer address to create the render target

	dev->CreateRenderTargetView(pBackBuffer, NULL, &backBuffer);

	pBackBuffer->Release();

	return true;*/

	return true;
}
bool Framework::InitializeGame(){
	return true;
}
void Framework::CleanD3D(){
}
Framework::~Framework(void){
}


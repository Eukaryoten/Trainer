#pragma once
#include <time.h>
#include "Timer.h"
#include "Window.h"
#include "Pipeline.h"


class Framework
{

public:
	Framework();
	Framework(HINSTANCE hInstance);

	bool Initialize();
	virtual bool InitializeGame();
	bool InitializeD3D(HWND hWnd);

	virtual void Update(float dt) = 0;
	virtual void Render() = 0;
	virtual void CleanD3D();

	int Run();
	void CalculateFrameStats();
	
	virtual ~Framework();
	
protected:
	Window *window;
	Pipeline *pipeline;
	Timer* timer;
	//ID3D11Device *dev;
	//ID3D11DeviceContext *devCon;
	//ID3D11RenderTargetView *backBuffer;
	//ID3D11DepthStencilView* depthStencilView;
	//ID3D11Texture2D* depthStencilBuffer;
	//ID3D11SamplerState* samplerState;
	//IDXGISwapChain *swapChain;
	//ID3D11InputLayout *inputLayout;
	//ID3D11Buffer *devObjectConstantBuffer;
	//ID3D11Buffer *devFrameConstantBuffer;
	//ObjectConstantBuffer cbPerObj; // Constant buffer per object
	//FrameConstantBuffer cbPerFrame; // Constant buffer per frame

	WPARAM cWParam;
	LPARAM cLParam;
};



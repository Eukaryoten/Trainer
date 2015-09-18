#pragma once
#include <Windows.h>
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>
#include <time.h>
#include <string>
#include <sstream>

#include "Timer.h"
#include "PipelineDefinitions.h"
#include "ApplicationDefinitions.h"

class Framework
{

public:
	Framework();
	Framework(HINSTANCE hInstance);

	virtual bool Initialize();
	virtual bool InitializeWindow();
	virtual bool InitializeD3D();
	virtual bool InitializeGame();

	virtual bool InitializeVertexBuffer();
	virtual bool InitializeIndexBuffer();
	virtual bool InitializeSwapChain();
	virtual bool InitializeInputLayout();
	virtual bool InitializeConstantBuffer();
	virtual bool InitializeViewPort();
	virtual bool InitializeDepthStencil();
	virtual bool InitializeSamplerState();

	virtual void Update(float dt) = 0;
	virtual void Render() = 0;
	virtual void CleanD3D();

	int Run();
	void CalculateFrameStats();
	
	LRESULT MessageProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	virtual ~Framework();
	
protected:

	ID3D11InputLayout *inputLayout;

	ID3D11Buffer *devObjectConstantBuffer;
	ID3D11Buffer *devFrameConstantBuffer;

	ObjectConstantBuffer cbPerObj; // Constant buffer per object
	FrameConstantBuffer cbPerFrame; // Constant buffer per frame

	Timer* timer;
	std::wstring applicationTitle; 
	HWND hWindow; 
	HINSTANCE hInstance;
	DWORD windowStyle;
	LPCSTR windowClassName;
	WPARAM cWParam;
	LPARAM cLParam;


	IDXGISwapChain *swapChain;
	ID3D11Device *dev;     
	ID3D11DeviceContext *devCon;
	ID3D11RenderTargetView *backBuffer; 
	ID3D11DepthStencilView* depthStencilView;
	ID3D11Texture2D* depthStencilBuffer;
	ID3D11SamplerState* samplerState;
	

};



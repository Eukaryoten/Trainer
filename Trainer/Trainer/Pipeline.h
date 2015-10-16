#pragma once
#include "PipelineDefinitions.h"
#include "WindowDefinitions.h"

class Pipeline
{
public:
	Pipeline();

	bool InitializeWindowSettings(HWND hWnd);

	void SetObjectBufferWVP();


	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetDeviceContext();
	IDXGISwapChain* GetSwapChain();
	ID3D11Buffer *GetObjectConstantBuffer();
	ID3D11Buffer *GetFrameConstantBuffer();
	ObjectConstantBuffer GetObjectStructure();
	FrameConstantBuffer GetFrameStructure();
	ID3D11RenderTargetView* GetBackBuffer();
	ID3D11DepthStencilView* GetDepthStencilView();

	~Pipeline();
private:

	ID3D11InputLayout *inputLayout;
	ID3D11Buffer *devObjectConstantBuffer;
	ID3D11Buffer *devFrameConstantBuffer;
	ObjectConstantBuffer cbPerObj; // Constant buffer per object
	FrameConstantBuffer cbPerFrame; // Constant buffer per frame
	IDXGISwapChain *swapChain;
	ID3D11Device *dev;
	ID3D11DeviceContext *devCon;
	ID3D11RenderTargetView *backBuffer;
	ID3D11DepthStencilView* depthStencilView;
	ID3D11Texture2D* depthStencilBuffer;
	ID3D11SamplerState* samplerState;
};


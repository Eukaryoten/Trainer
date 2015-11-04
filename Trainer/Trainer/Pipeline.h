#pragma once
#include "PipelineDefinitions.h"
#include "WindowDefinitions.h"
#include "ShaderObject.h"


class Pipeline
{
public:
	Pipeline();

	bool InitializeWindowSettings(HWND);
	bool InitializeDirect3D();
	bool InitializeShaderObjects();

	bool InitializeDepthStencil();
	bool InitializeViewportAndSampler();
	bool InitializeConstantBuffers();
	

	void SetShaderObject(ShaderObjectType);

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

	ShaderObject* shaderList[2];
	Light pointLight;

	ID3D11Buffer *devObjectConstantBuffer;
	ID3D11Buffer *devFrameConstantBuffer;
	ObjectConstantBuffer cbPerObj;
	FrameConstantBuffer cbPerFrame;
	IDXGISwapChain *swapChain;
	ID3D11Device *dev;
	ID3D11DeviceContext *devCon;
	ID3D11RenderTargetView *backBuffer;
	ID3D11DepthStencilView* depthStencilView;
	ID3D11Texture2D* depthStencilBuffer;
	ID3D11SamplerState* samplerState;
};


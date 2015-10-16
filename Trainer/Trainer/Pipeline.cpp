#include "Pipeline.h"



Pipeline::Pipeline(){
}

bool Pipeline::InitializeWindowSettings(HWND hWindow) {

	DXGI_MODE_DESC bufferDesc;

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

	return true;
}

bool Pipeline::InitializeDirect3D() {

	D3D11_TEXTURE2D_DESC depthStencilDesc;

	depthStencilDesc.Width = SCREEN_WIDTH;
	depthStencilDesc.Height = SCREEN_HEIGHT;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc.SampleDesc.Count = 1;
	depthStencilDesc.SampleDesc.Quality = 0;
	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;

	dev->CreateTexture2D(&depthStencilDesc, NULL, &depthStencilBuffer);
	dev->CreateDepthStencilView(depthStencilBuffer, NULL, &depthStencilView);
	devCon->OMSetRenderTargets(1, &backBuffer, depthStencilView);

	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = SCREEN_WIDTH;
	viewport.Height = SCREEN_HEIGHT;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	D3D11_SAMPLER_DESC sampDesc;

	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

	dev->CreateSamplerState(&sampDesc, &samplerState);

	// Update Pipeline

	devCon->PSSetSamplers(0, 1, &samplerState);
	devCon->RSSetViewports(1, &viewport);

	// Create object constant buffer

	D3D11_BUFFER_DESC constantBufferDesc;
	ZeroMemory(&constantBufferDesc, sizeof(D3D11_BUFFER_DESC));
	constantBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	constantBufferDesc.ByteWidth = sizeof(cbPerObj);

	if ((constantBufferDesc.ByteWidth % 16) != 0)
		constantBufferDesc.ByteWidth += 16 - (constantBufferDesc.ByteWidth % 16);

	constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constantBufferDesc.CPUAccessFlags = 0;
	constantBufferDesc.MiscFlags = 0;
	dev->CreateBuffer(&constantBufferDesc, NULL, &devObjectConstantBuffer);

	devCon->VSSetConstantBuffers(0, 1, &devObjectConstantBuffer);
	devCon->PSSetConstantBuffers(0, 1, &devObjectConstantBuffer);

	// Create frame constant buffer

	ZeroMemory(&constantBufferDesc, sizeof(D3D11_BUFFER_DESC));

	constantBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	constantBufferDesc.ByteWidth = sizeof(cbPerFrame);

	if ((constantBufferDesc.ByteWidth % 16) != 0)
		constantBufferDesc.ByteWidth += 16 - (constantBufferDesc.ByteWidth % 16);

	constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constantBufferDesc.CPUAccessFlags = 0;
	constantBufferDesc.MiscFlags = 0;

	dev->CreateBuffer(&constantBufferDesc, NULL, &devFrameConstantBuffer);

	return true;

}

ID3D11Device* Pipeline::GetDevice() {
	return dev;
}

ID3D11DeviceContext* Pipeline::GetDeviceContext() {
	return devCon;
}

IDXGISwapChain* Pipeline::GetSwapChain() {
	return swapChain;
}
ID3D11Buffer* Pipeline::GetObjectConstantBuffer() {
	return devObjectConstantBuffer;
}
ID3D11Buffer* Pipeline::GetFrameConstantBuffer() {
	return devFrameConstantBuffer;
}
ObjectConstantBuffer Pipeline::GetObjectStructure() {
	return cbPerObj;
}
FrameConstantBuffer Pipeline::GetFrameStructure() {
	return cbPerFrame;
}

ID3D11RenderTargetView* Pipeline::GetBackBuffer() {
	return backBuffer;
}

ID3D11DepthStencilView* Pipeline::GetDepthStencilView() {
	return depthStencilView;
}


Pipeline::~Pipeline(){

	devObjectConstantBuffer->Release();
	devFrameConstantBuffer->Release();
	swapChain->SetFullscreenState(FALSE, NULL);
	swapChain->Release();
	backBuffer->Release();
	dev->Release();
	devCon->Release();
	depthStencilBuffer->Release();
	depthStencilView->Release();

}

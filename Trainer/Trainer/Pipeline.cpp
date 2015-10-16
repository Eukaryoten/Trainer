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

#pragma once

#include "Framework.h"


namespace{
	Framework* pFramework;
}

Framework::Framework(void){

}
Framework::Framework(HINSTANCE hInstance){
	hInstance = hInstance;
	hWindow = NULL;
	applicationTitle = L"Game Engine";
	windowStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
	windowClassName = "APPWINDOWCLASS";
	pFramework = this;
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
LRESULT Framework::MessageProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam){
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE){
			DestroyWindow(hWnd);
		}
		return 0;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam){
	return pFramework->MessageProc(hWnd, msg, wParam, lParam);
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

		std::wostringstream outs;
		outs.precision(6);
		outs << applicationTitle << L"Game Engine "
			<< L"FPS: " << fps << L"    "
			<< L"Frame Time: " << mspf << L" (ms)";
		SetWindowText(hWindow, outs.str().c_str());

		// Reset for next average.
		frameCnt = 0;
		timeElapsed += 1.0f;
	}
}

bool Framework::Initialize(){
	if (!InitializeWindow()) return false;
	if (!InitializeD3D()) return false;
	if (!InitializeGame()) return false;
	return true;
}
bool Framework::InitializeWindow(){

	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName = L"WindowClass";
	RegisterClassEx(&wc);

	hWindow = CreateWindowEx(NULL,
		L"WindowClass",    // name of the window class
		applicationTitle.c_str(),   // title of the window
		WS_OVERLAPPEDWINDOW,    // window style
		WINDOW_POSITIONX,    // x-position of the window
		WINDOW_POSITIONY,    // y-position of the window
		SCREEN_WIDTH,    // width of the window
		SCREEN_HEIGHT,    // height of the window
		NULL,    // we have no parent window, NULL
		NULL,    // we aren't using menus, NULL
		hInstance,    // application handle
		NULL);    // used with multiple windows, NULL

	if (!hWindow){
		MessageBoxA(NULL, "Failed to create window", NULL, NULL);
		return false;
	}

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

	ShowWindow(hWindow, SW_SHOW);


	return true;
}
bool Framework::InitializeD3D(){

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
	dev->CreateBuffer(&constantBufferDesc, NULL, &constantObjectBuffer);

	devCon->VSSetConstantBuffers(0, 1, &constantObjectBuffer);
	devCon->PSSetConstantBuffers(0, 1, &constantObjectBuffer);

	// Create frame constant buffer

	ZeroMemory(&constantBufferDesc, sizeof(D3D11_BUFFER_DESC));

	constantBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	constantBufferDesc.ByteWidth = sizeof(cbPerFrame);
	constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constantBufferDesc.CPUAccessFlags = 0;
	constantBufferDesc.MiscFlags = 0;

	dev->CreateBuffer(&constantBufferDesc, NULL, &constantFrameBuffer);



	return true;
}

bool Framework::InitializeGame(){
	return true;
}

bool Framework::InitializeVertexBuffer(){
	return true;
}
bool Framework::InitializeIndexBuffer(){
	return true;
}
bool Framework::InitializeSwapChain(){
	return true;
}
bool Framework::InitializeInputLayout(){
	return true;
}
bool Framework::InitializeConstantBuffer(){
	return true;
}
bool Framework::InitializeViewPort(){
	return true;
}
bool Framework::InitializeDepthStencil(){
	return true;
}
bool Framework::InitializeSamplerState(){
	return true;
}
void Framework::CleanD3D(){

	// Free Memory and Pointers

	constantObjectBuffer->Release();
	constantFrameBuffer->Release();

	swapChain->SetFullscreenState(FALSE, NULL);
	swapChain->Release();
	backBuffer->Release();
	dev->Release();
	devCon->Release();
	depthStencilBuffer->Release();
	depthStencilView->Release();

}
Framework::~Framework(void){
	CleanD3D();
}


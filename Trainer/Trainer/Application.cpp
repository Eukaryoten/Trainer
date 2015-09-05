#include "Application.h"


Application::Application(HINSTANCE hInstance){

	timer = new Timer();
	gManager = new GeometryManager();

}

bool Application::InitializeGame(){

	gManager->LoadData();
	gManager->LoadVertexBuffer(dev);
	gManager->LoadIndexBuffer(dev);

	gManager->SetVertexBuffer(devCon);
	gManager->SetIndexBuffer(devCon);

	return true;
}

void Application::Update(float dt){

}

void Application::Render(){

	devCon->ClearRenderTargetView(backBuffer, D3DXCOLOR(0.0,0.0,0.0,0.0));
	devCon->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	devCon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);


	// Render stuff here


	swapChain->Present(0, 0);

}

Application::~Application(){
}

#include "Application.h"


Application::Application(HINSTANCE hInstance){

	timer = new Timer();
	gManager = new GeometryManager();

	currentPosition = D3DXVECTOR3(10.0f, 0.0f, 5.0f);
	currentTarget = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	currentUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
}

bool Application::InitializeGame(){


	defaultShader = new Shader(dev, L"DefaultShader.shader");

	devCon->IASetInputLayout(inputLayout);

	gManager->LoadData();
	gManager->LoadVertexBuffer(dev);
	gManager->LoadIndexBuffer(dev);

	gManager->SetVertexBuffer(devCon);
	gManager->SetIndexBuffer(devCon);


	D3DXMatrixPerspectiveFovLH(&projection, 0.4*3.14f, (float)(SCREEN_WIDTH / SCREEN_HEIGHT), 1.0f, 1000.0f); // Set the cameras aspect ratio
	D3DXMatrixLookAtLH(&view, &currentPosition, &currentTarget, &currentUp);

	return true;
}

void Application::Update(float dt){

	D3DXMatrixIdentity(&world);
	WVP = world * view * projection; // Get the WVP to send to constant buffer


	D3DXMatrixTranspose(&cbPerObj.WVP, &WVP); // Send WVP to constant buffer
	devCon->UpdateSubresource(defaultConstantBuffer, 0, NULL, &cbPerObj, 0, 0);


}

void Application::Render(){

	devCon->ClearRenderTargetView(backBuffer, D3DXCOLOR(0.0,0.0,0.0,0.0));
	devCon->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	devCon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	defaultShader->SetAsCurrentShader(devCon);

	devCon->DrawIndexed(36,0,0);

	// Render stuff here

	swapChain->Present(0, 0);

}

Application::~Application(){
}

#include "Application.h"

Application::Application(HINSTANCE hInstance){

	timer = new Timer();
	gManager = new GeometryManager();
	test = new GameObject();
	rot = 0;

	// Temporary Camera Initialization

	currentPosition = D3DXVECTOR3(10.0f, 0.0f, 5.0f);
	currentTarget = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	currentUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	// Directional Light Initialization

	light.dir = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 0.0);
	light.ambient = D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f);
	light.diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);


	// Point Light Initialization

	pLight.pos = D3DXVECTOR4(0.0f, 0.0f, 0.0f,0.0f);
	pLight.amb = D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f);
	pLight.dif = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	pLight.att = D3DXVECTOR4(0.0f, 0.2f, 0.0f,0.0f);
	pLight.range = 100.0f;
}

bool Application::InitializeGame(){

	directionalLight = new Shader(dev, L"DirectionalLight.shader", Vertex::NormalLayout);

	gManager->LoadData();
	gManager->LoadVertexBuffer(dev);
	gManager->LoadIndexBuffer(dev);

	gManager->SetVertexBuffer(devCon);
	gManager->SetIndexBuffer(devCon);

	D3DXMatrixPerspectiveFovLH(&projection, 0.4*3.14f, (float)(SCREEN_WIDTH / SCREEN_HEIGHT), 1.0f, 1000.0f); // Set the cameras aspect ratio
	D3DXMatrixLookAtLH(&view, &currentPosition, &currentTarget, &currentUp);

	cbPerFrame.light = light;
	devCon->UpdateSubresource(devFrameConstantBuffer, 0, NULL, &cbPerFrame,0,0);
	devCon->PSSetConstantBuffers(0, 1, &devFrameConstantBuffer);

	return true;
}

void Application::Update(float dt){

	rot += 0.5 * dt;
	test->SetRotation(D3DXVECTOR3(rot,rot,rot));
}

void Application::Render(){

	devCon->ClearRenderTargetView(backBuffer, D3DXCOLOR(0.0,0.0,0.0,0.0));
	devCon->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	devCon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	directionalLight->SetShader(devCon);

	test->Draw(devCon, devObjectConstantBuffer, &cbPerObj, view*projection);

	swapChain->Present(0, 0);

}

Application::~Application(){
}

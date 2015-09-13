#include "Application.h"

Application::Application(HINSTANCE hInstance){

	timer = new Timer();
	gManager = new GeometryManager<Vertex::ColouredNormal>();
	player = new GameObject();
	rot = 0;

	// Temporary Camera Initialization

	currentPosition = D3DXVECTOR3(10.0f, 0.0f, 5.0f);
	currentTarget = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	currentUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	// Directional Light Initialization

	directionalLight.dir = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 0.0);
	directionalLight.amb = D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f);
	directionalLight.dif = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);


	// Point Light Initialization

	pointLight.pos = D3DXVECTOR4(10.0f, 0.0f, 0.0f,0.0f);
	pointLight.amb = D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f);
	pointLight.dif = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	pointLight.att = D3DXVECTOR4(0.0f, 0.2f, 0.0f,0.0f);
	pointLight.range = 100.0f;
}

bool Application::InitializeGame(){

	directionalLightShader = new Shader(dev, L"DirectionalLight.shader", Vertex::ColouredNormalLayout);
	pointLightShader = new Shader(dev, L"PointLight.shader", Vertex::ColouredNormalLayout);

	gManager->Initialize(dev,devCon);

	D3DXMatrixPerspectiveFovLH(&projection, 0.4*3.14f, (float)(SCREEN_WIDTH / SCREEN_HEIGHT), 1.0f, 1000.0f); // Set the cameras aspect ratio
	D3DXMatrixLookAtLH(&view, &currentPosition, &currentTarget, &currentUp);

	cbPerFrame.light = pointLight;
	devCon->UpdateSubresource(devFrameConstantBuffer, 0, NULL, &cbPerFrame,0,0);
	devCon->PSSetConstantBuffers(0, 1, &devFrameConstantBuffer);

	return true;
}

void Application::Update(float dt){

	rot += 1.0 * dt;
	player->SetRotation(D3DXVECTOR3(0.0,rot,0.0));
}

void Application::Render(){

	devCon->ClearRenderTargetView(backBuffer, D3DXCOLOR(0.0,0.0,0.0,0.0));
	devCon->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	devCon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	pointLightShader->SetShader(devCon);

	player->Draw(devCon, devObjectConstantBuffer, &cbPerObj, view*projection);

	swapChain->Present(0, 0);

}

Application::~Application(){
}

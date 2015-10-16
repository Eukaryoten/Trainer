#include "Application.h"

namespace {

	Application* pApp;
}

Application::Application(HINSTANCE hInstance){

	window = new Window(hInstance);
	pipeline = new Pipeline();
	timer = new Timer();
	

	// Object memory allocation

	pApp = this;
	camera = new Camera(&projection);
	timer = new Timer();
	gManager = new GeometryManager<Vertex::ColouredNormal>();
	
	// Character Initialization

	player = new GameObject(0.0,0.5,1.0);
	enemy  = new GameObject(1.0,0.0,0.0);
	floor  = new GameObject(1.0,0.5,0.0);

	player->SetPosition(D3DXVECTOR3(3.0, 0.0, 0.0));
	enemy->SetPosition(D3DXVECTOR3(-3.0, 0.0, 0.0));
	floor->SetPosition(D3DXVECTOR3(0.0, -1.0, 0.0));

	player->SetScale(D3DXVECTOR3(0.3, 0.3, 0.3));
	enemy->SetScale(D3DXVECTOR3(0.3, 0.3, 0.3));
	floor->SetScale(D3DXVECTOR3(10.0, 0.2, 4.0));

	// Directional Light Initialization

	directionalLight.dir = D3DXVECTOR4(0.0f, 0.0f, 0.2f, 0.0) ;
	directionalLight.amb = D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f);
	directionalLight.dif = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);

	// Point Light Initialization

	pointLight.pos = D3DXVECTOR4(0.0f, 1000.0f, -40.0f, 0.0f);
	pointLight.amb = D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f);
	pointLight.dif = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	pointLight.att = D3DXVECTOR4(0.5f, 0.0f, 0.0f, 0.0f);
	pointLight.range = 10000.0f;
}

bool Application::InitializeGame(){

	ID3D11Device *dev = pipeline->GetDevice();
	ID3D11DeviceContext *devCon = pipeline->GetDeviceContext();
	IDXGISwapChain *swapChain = pipeline->GetSwapChain();
	ID3D11Buffer *objCB = pipeline->GetObjectConstantBuffer();
	ID3D11Buffer *frmCB = pipeline->GetFrameConstantBuffer();
	ObjectConstantBuffer *cbPerObj = &pipeline->GetObjectStructure();
	FrameConstantBuffer *cbPerFrame = &pipeline->GetFrameStructure();

	directionalLightShader = new Shader(dev, L"DirectionalLight.shader", Vertex::ColouredNormalLayout);
	pointLightShader = new Shader(dev, L"PointLight.shader", Vertex::ColouredNormalLayout);

	gManager->Initialize(dev, devCon);

	cbPerFrame->light = pointLight;
	devCon->UpdateSubresource(&frmCB, 0, NULL, &cbPerFrame,0,0);
	devCon->PSSetConstantBuffers(0, 1, &frmCB);

	return true;
}

void Application::Update(float dt){

	window->Update(dt);
	camera->Update(&view);
	
	player->SetRotation(D3DXVECTOR3(0.0,-rot, 0.0));
	enemy->SetRotation(D3DXVECTOR3(0.0, rot, 0.0));

}

void Application::Render(){

	ID3D11Device *dev = pipeline->GetDevice();
	ID3D11DeviceContext *devCon = pipeline->GetDeviceContext();
	IDXGISwapChain *swapChain = pipeline->GetSwapChain();
	ID3D11Buffer *objCB = pipeline->GetObjectConstantBuffer();
	ID3D11Buffer *frmCB = pipeline->GetFrameConstantBuffer();
	ObjectConstantBuffer *cbPerObj = &pipeline->GetObjectStructure();
	FrameConstantBuffer *cbPerFrame = &pipeline->GetFrameStructure();


	devCon->ClearRenderTargetView(pipeline->GetBackBuffer(), D3DXCOLOR(0.0,0.0,0.0,0.0));
	devCon->ClearDepthStencilView(pipeline->GetDepthStencilView(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	// Drawing starts here

	pointLightShader->SetShader(devCon);

	player->Draw(devCon, objCB, cbPerObj, view*projection);
	enemy->Draw(devCon, objCB, cbPerObj, view*projection);
	//floor->Draw(devCon, devObjectConstantBuffer, &cbPerObj, view*projection);


	devCon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);

	RotateWVP(D3DXVECTOR3(0.0,0.0,0.0));

	gManager->DrawLineFromCircleCentre(devCon, rot);


	devCon->Draw(gManager->GetSphereVertexCount(),gManager->GetCubeVertexCount());

	// End of drawing

	swapChain->Present(0, 0);

}

void Application::RotateWVP(D3DXVECTOR3 rot) {

	ID3D11Device *dev = pipeline->GetDevice();
	ID3D11DeviceContext *devCon = pipeline->GetDeviceContext();
	IDXGISwapChain *swapChain = pipeline->GetSwapChain();
	ID3D11Buffer *objCB = pipeline->GetObjectConstantBuffer();
	ID3D11Buffer *frmCB = pipeline->GetFrameConstantBuffer();
	ObjectConstantBuffer *cbPerObj = &pipeline->GetObjectStructure();
	FrameConstantBuffer *cbPerFrame = &pipeline->GetFrameStructure();



	D3DXMatrixIdentity(&world);

	D3DXMATRIX rotationMatrix;

	D3DXMATRIX xRot;
	D3DXMATRIX yRot;
	D3DXMATRIX zRot;

	D3DXMatrixRotationX(&xRot, rot.x);
	D3DXMatrixRotationY(&yRot, rot.y);
	D3DXMatrixRotationZ(&zRot, rot.z);

	rotationMatrix = xRot * yRot * zRot;

	world *= rotationMatrix;

	WVP = world * view * projection;

	D3DXMatrixTranspose(&cbPerObj->WVP, &WVP); // Send WVP to constant buffer
	D3DXMatrixTranspose(&cbPerObj->world, &world);
	cbPerObj->colour = D3DXVECTOR3(1.0, 1.0, 1.0);

	devCon->UpdateSubresource(objCB, 0, NULL, &cbPerObj, 0, 0);
}


Application::~Application(){
}

#include "Application.h"

Application::Application(HINSTANCE hInstance){

	window = new WindowObject(hInstance);
	mouse = new MouseObject();
	pipeline = new PipelineObject();
	timer = new TimerObject();
	currentDrawSettings = new DrawObjectSettings();
	
	// Object memory allocation

	camera = new CameraObject(&projection);
	timer = new TimerObject();
	gManager = new GeometryManager<Vertex::ColouredNormal>();
	
	// Character Initialization

	player = new GameObject(1.0,0.0,1.0);
	enemy  = new GameObject(1.0,0.0,0.0);
	floor  = new GameObject(0.0,0.5,0.5);

	player->SetPosition(D3DXVECTOR3(0.0, 0.0, 0.0));
	enemy->SetPosition(D3DXVECTOR3(-3.0, 0.0, 0.0));
	floor->SetPosition(D3DXVECTOR3(0.0, -1.0, 0.0));

	player->SetScale(D3DXVECTOR3(0.3, 0.3, 0.3));
	enemy->SetScale(D3DXVECTOR3(0.3, 0.3, 0.3));
	floor->SetScale(D3DXVECTOR3(100.0, 0.2, 100.0));

	// Directional Light Initialization

	directionalLight.dir = D3DXVECTOR4(0.0f, 0.0f, 0.2f, 0.0) ;
	directionalLight.amb = D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f);
	directionalLight.dif = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);

	// Point Light Initialization

	pointLight.pos = D3DXVECTOR4(0.0f, 100.0f, -40.0f, 0.0f);
	pointLight.amb = D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f);
	pointLight.dif = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	pointLight.att = D3DXVECTOR4(0.5f, 0.0f, 0.0f, 0.0f);
	pointLight.range = 1000.0f;
}

bool Application::InitializeGame(){

	ID3D11Buffer *objCB = pipeline->GetObjectConstantBuffer();
	ID3D11Buffer *frmCB = pipeline->GetFrameConstantBuffer();

	// ********** The last line in this code does not assign the point light to the frame constant Buffer. ******** \\

	FrameConstantBuffer *fcb = &pipeline->GetFrameStructure();
	fcb->light = pointLight; 

	pipeline->GetFrameStructure().light = pointLight; // Need to examine why this line doesn't work and the others do
	// Is it because it's just not being stored? What is it returning?

	// ********** The last line in this code does not assign the point light to the frame constant Buffer. ******** \\



	gManager->Initialize(pipeline->GetDevice(), pipeline->GetDeviceContext());
	pipeline->GetDeviceContext()->VSSetConstantBuffers(0, 1, &objCB);
	pipeline->GetDeviceContext()->PSSetConstantBuffers(0, 1, &frmCB);

	
	pipeline->GetDeviceContext()->UpdateSubresource(frmCB, 0, NULL, fcb,0,0);

	return true;
}

void Application::Update(float dt){

	float mSpeed = 6;
	float rSpeed = 2;


	window->Update(dt);
	mouse->Update(dt);
	camera->Update(&view);
	camera->FollowTarget(player, 10);

	if (KeyboardState::GetLeftKey())  camera->Rotate(D3DXVECTOR3(-rSpeed*dt, 0.0, 0));
	if (KeyboardState::GetRightKey()) camera->Rotate(D3DXVECTOR3( rSpeed*dt, 0.0, 0));

	if (KeyboardState::GetWKey()) camera->TranslatePositionAlongLocalAxis(D3DXVECTOR3(0.0,0.0, mSpeed*dt));
	if (KeyboardState::GetAKey()) camera->TranslatePositionAlongLocalAxis(D3DXVECTOR3(-mSpeed*dt, 0.0,0.0));
	if (KeyboardState::GetSKey()) camera->TranslatePositionAlongLocalAxis(D3DXVECTOR3(0.0, 0.0, -mSpeed*dt));
	if (KeyboardState::GetDKey()) camera->TranslatePositionAlongLocalAxis(D3DXVECTOR3(mSpeed*dt, 0.0, 0.0));


	if (window->BoolMouseObjectInWindowObject(mouse)) {
		camera->Rotate(D3DXVECTOR3(mouse->GetDeltaMouseObjectPosition(dt).x*0.01,
			mouse->GetDeltaMouseObjectPosition(dt).y*0.01,
								   0));
		ShowCursor(false);
	}

	window->BindMouseObjectToWindowObject(mouse);
	player->SetRotation(D3DXVECTOR3(0.0,-rot, 0.0));
	enemy->SetRotation(D3DXVECTOR3(0.0, rot, 0.0));

}

void Application::UpdateDrawSettings() {

	currentDrawSettings->devCon = pipeline->GetDeviceContext();
	currentDrawSettings->devConstantBuffer = pipeline->GetObjectConstantBuffer();
	currentDrawSettings->constantBuffer = &pipeline->GetObjectStructure();
	currentDrawSettings->viewProjection = view*projection;
}

void Application::Render(){

	UpdateDrawSettings();

	pipeline->GetDeviceContext()->ClearRenderTargetView(pipeline->GetBackBuffer(), D3DXCOLOR(0.0,0.0,0.0,0.0));
	pipeline->GetDeviceContext()->ClearDepthStencilView(pipeline->GetDepthStencilView(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	// Drawing starts here

	pipeline->SetShaderObject(PointLight);

	player->Draw(currentDrawSettings);
	enemy->Draw(currentDrawSettings);
	floor->Draw(currentDrawSettings);


	// End of drawing

	pipeline->GetSwapChain()->Present(0, 0);

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

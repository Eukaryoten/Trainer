#pragma once

#include "ApplicationDefinitions.h"
#include "Framework.h"
#include "Camera.h"
#include "GameObject.h"
#include "GeometryManager.h"

class Application : public Framework
{
public:

	Application(HINSTANCE hInstance);
	bool InitializeGame();
	void UpdateDrawSettings();

	void RotateWVP(D3DXVECTOR3);
	void Update(float dt);
	void Render();

	~Application();

private:

	DrawObjectSettings *currentDrawSettings;

	Camera *camera;

	float rot;

	Light directionalLight;
	Light pointLight;

	GameObject *player;
	GameObject *enemy;
	GameObject *floor;

	GeometryManager<Vertex::ColouredNormal>* gManager;

	D3DXMATRIX WVP;
	D3DXMATRIX world;
	D3DXMATRIX view;
	D3DXMATRIX projection;
	D3DXVECTOR3 currentPosition;
	D3DXVECTOR3 currentTarget;
	D3DXVECTOR3 currentUp;

};


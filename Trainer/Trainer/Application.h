#pragma once

#include "Framework.h"
#include "Shader.h"
#include "GameObject.h"
#include "GeometryManager.h"

class Application : public Framework
{
public:
	Application(HINSTANCE hInstance);

	bool InitializeGame();
	void Update(float dt);
	void Render();

	~Application();

private:


	float rot;

	Light light;
	PointLight pLight;

	GameObject *test;
	GeometryManager* gManager;

	Shader* currentShader;
	Shader* directionalLight;

	D3DXMATRIX WVP; // World Matrix * View Matrix * Projection Matrix - Helper attribute which is used to transform object into camera space
	D3DXMATRIX world;
	D3DXMATRIX view;
	D3DXMATRIX projection;
	D3DXVECTOR3 currentPosition;
	D3DXVECTOR3 currentTarget;
	D3DXVECTOR3 currentUp;

};


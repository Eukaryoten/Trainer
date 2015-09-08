#pragma once
#include "Framework.h"
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

	GeometryManager* gManager;
	Shader* defaultShader;

	D3DXMATRIX WVP; // World Matrix * View Matrix * Projection Matrix - Helper attribute which is used to transform object into camera space
	D3DXMATRIX world;
	D3DXMATRIX view;
	D3DXMATRIX projection;
	D3DXVECTOR3 currentPosition;
	D3DXVECTOR3 currentTarget;
	D3DXVECTOR3 currentUp;

};


#pragma once
#include "Base.h"
#include "ApplicationDefinitions.h"

class GameObject : public Base
{
public:
	GameObject(float r, float g, float b);

	virtual void Draw(DrawObjectSettings*);
	virtual void GameObject::Draw(ID3D11DeviceContext*, ID3D11Buffer*, ObjectConstantBuffer*,D3DXMATRIX);

	virtual void Update(float dt);

	void CleanUp();
	~GameObject();

protected:

	D3DXVECTOR3 colourRGB;

};


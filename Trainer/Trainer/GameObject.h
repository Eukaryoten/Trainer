#pragma once
#include "Base.h"

class GameObject : public Base
{
public:
	GameObject();

	virtual void Draw(ID3D11DeviceContext*, ID3D11Buffer*, D3DXMATRIX);
	void Initialize(ObjectConstantBuffer* cb);
	virtual void Update(float dt);

	void CleanUp();
	~GameObject();

protected:

	ObjectConstantBuffer* constantBuffer; // Pointer to constant buffer object used to send information to shaders

};


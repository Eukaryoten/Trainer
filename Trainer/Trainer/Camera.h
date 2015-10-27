#pragma once
#include "Base.h"
#include "WindowDefinitions.h"


class Camera : public Base
{
public:
	Camera(D3DXMATRIX*);
	void Rotate(D3DXVECTOR3);
	void Update(D3DXMATRIX*);
	void SetYawPitch(D3DXVECTOR2);
	void CleanUp();
	~Camera();
private:


	float yaw;
	float pitch;
	D3DXMATRIX view; // The cameras view matrix
	D3DXVECTOR3 target; // The position the camera is "looking at"
	D3DXMATRIX projection; // Aspect ratio


};


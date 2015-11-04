#pragma once
#include "BaseObject.h"
#include "WindowDefinitions.h"


class CameraObject : public BaseObject
{
public:
	CameraObject(D3DXMATRIX*);
	void Rotate(D3DXVECTOR3);
	void Update(D3DXMATRIX*);
	void SetYawPitch(D3DXVECTOR2);
	void FollowTarget(BaseObject*,float);
	void FreeCameraObject();
	void CleanUp();
	~CameraObject();
private:


	float yaw;
	float pitch;
	D3DXMATRIX view; // The CameraObjects view matrix
	D3DXVECTOR3 target; // The position the CameraObject is "looking at"
	D3DXMATRIX projection; // Aspect ratio


};


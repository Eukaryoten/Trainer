#include "Camera.h"



Camera::Camera(D3DXMATRIX* worldProjection){

	// Temporary Camera Initialization

	currentUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	currentPosition = D3DXVECTOR3(0.0f, 2.0f, 10.0f);
	target = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXMatrixPerspectiveFovLH(&projection, 0.4*3.14f, (float)(SCREEN_WIDTH / SCREEN_HEIGHT), 1.0f, 1000.0f); // Set the cameras aspect ratio

	axisOffset.x = 0;
	axisOffset.y = 0;
	axisOffset.z = 0;

	yaw = 0.0;
	pitch = 0.0;
	
	*worldProjection = projection;
}

void Camera::Update(D3DXMATRIX *worldView) {

	D3DXMatrixRotationYawPitchRoll(&rotationMatrix, yaw, pitch, 0); // Store the rotation matrix
	D3DXVec3TransformCoord(&target, &defaultForward, &rotationMatrix); // Transform the forward vector by the rotation matrix and store in target
	D3DXVec3Normalize(&target, &target); // Normalize the current target

    // Temporary matrix to store pitch rotation

	D3DXMATRIX RotateYTempMatrix;
	D3DXMatrixRotationY(&RotateYTempMatrix, pitch);

	// Transform default direction vectors by rotation matrix to obtain new update direction vectors

	D3DXVec3TransformCoord(&currentRight, &defaultRight, &rotationMatrix);
	D3DXVec3TransformCoord(&currentUp, &defaultUp, &rotationMatrix);
	D3DXVec3TransformCoord(&currentForward, &defaultForward, &rotationMatrix);

	// Translate current position by scaled direction vectors

	currentPosition += axisOffset.x*currentRight;
	currentPosition += axisOffset.z*currentForward;

	// Reset scalars after done with translation

	axisOffset.x = 0.0f;
	axisOffset.z = 0.0f;

	// Set new view matrix with current target and new up direction vector

	//currentPosition = D3DXVECTOR3(0.0f, 0.0f, 10.0f);
	//target = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//currentUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	target = currentPosition + target;


	D3DXMatrixLookAtLH(&view, &currentPosition, &target, &currentUp);

	*worldView = view;

}

void Camera::Rotate(D3DXVECTOR3 rot) {
	yaw += rot.x;
	pitch += rot.y;
}

void Camera::CleanUp() {

}


Camera::~Camera(){
}

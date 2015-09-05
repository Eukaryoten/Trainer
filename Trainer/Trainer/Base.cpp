#include "Base.h"


Base::Base(){

	// Initialize attributes

	defaultRight = D3DXVECTOR3(1.0f, 0.0f, 0.0f); // Set default Right direction to be positive 1 in the x-axis
	defaultUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f); // Set default Up direction to be positive 1 in the y-axis
	defaultForward = D3DXVECTOR3(0.0f, 0.0f, 1.0f); // Set default Forward direction to be positive 1 in the z-axis

	D3DXMatrixIdentity(&world);
	D3DXMatrixIdentity(&rotationMatrix);
	D3DXMatrixIdentity(&translationMatrix);
	D3DXMatrixIdentity(&scaleMatrix);

	currentRotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	currentPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	currentRight = defaultRight;
	currentUp = defaultUp;
	currentForward = defaultForward;

}

#pragma region Set Functions

void Base::SetRotationVector(D3DXVECTOR3 input){
	currentRotation = input;
}
void Base::SetCurrentForward(D3DXVECTOR3 input){
	currentForward = input;
}
void Base::SetCurrentRight(D3DXVECTOR3 input){
	currentRight = input;
}
void Base::SetLeftRightSpeed(float speed){
	moveLeftRight += speed;
}
void Base::SetBackForwardSpeed(float speed){
	moveBackForward += speed;
}
void Base::SetPosition(D3DXVECTOR3 pos){
	currentPosition = pos;
}

#pragma endregion

#pragma region Get Functions

D3DXMATRIX Base::GetMatrix(){
	return world;
}
D3DXVECTOR3 Base::GetPosition(){
	return currentPosition;
}
D3DXVECTOR3 Base::GetRightVector(){
	return currentRight;
}
void Base::GetPosition(D3DXVECTOR3& pos){
	pos = currentPosition;
}
D3DXVECTOR3 Base::GetFacingVector(){
	return currentForward;
}

#pragma endregion

#pragma region Update Functions

void Base::UpdateMatrices(){
	D3DXMatrixTranspose(&constantBuffer->WVP, &WVP); // Send WVP to constant buffer
}
void Base::UpdateGeometry(){

}

#pragma endregion

#pragma region Increment Functions

void Base::TranslateCurrentPosition(D3DXVECTOR3 pos){
	currentPosition += pos;
}

#pragma endregion

Base::~Base(){
}

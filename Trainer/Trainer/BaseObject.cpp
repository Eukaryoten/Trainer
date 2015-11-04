#include "BaseObject.h"


BaseObject::BaseObject(){

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

}
void BaseObject::SetRotation(D3DXVECTOR3 input){

	currentRotation = input;

	D3DXMATRIX xRot;
	D3DXMATRIX yRot;
	D3DXMATRIX zRot;

	D3DXMatrixRotationX(&xRot, currentRotation.x);
	D3DXMatrixRotationY(&yRot, currentRotation.y);
	D3DXMatrixRotationZ(&zRot, currentRotation.z);

	rotationMatrix = xRot * yRot * zRot;

}
void BaseObject::SetPosition(D3DXVECTOR3 pos){
	currentPosition = pos;
	D3DXMatrixTranslation(&translationMatrix, currentPosition.x, currentPosition.y, currentPosition.z);
}

void BaseObject::SetScale(D3DXVECTOR3 scale) {
	currentScale = scale;
	D3DXMatrixScaling(&scaleMatrix, currentScale.x, currentScale.y, currentScale.z);
}

D3DXMATRIX BaseObject::GetMatrix(){
	return world;
}
D3DXVECTOR3 BaseObject::GetPosition(){
	return currentPosition;
}

void BaseObject::TranslatePosition(D3DXVECTOR3 pos){
	currentPosition += pos;
	D3DXMatrixTranslation(&translationMatrix, currentPosition.x, currentPosition.y, currentPosition.z);
}

void BaseObject::TranslatePositionAlongLocalAxis(D3DXVECTOR3 offset) {

	D3DXVECTOR3 lastAxisPosition = localAxisPosition;
	localAxisPosition = offset;

	if (offset.x == 0) localAxisPosition.x = lastAxisPosition.x;
	if (offset.y == 0) localAxisPosition.y = lastAxisPosition.y;
	if (offset.z == 0) localAxisPosition.z = lastAxisPosition.z;
	
}

BaseObject::~BaseObject(){
}

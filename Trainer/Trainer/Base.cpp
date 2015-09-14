#include "Base.h"


Base::Base(){

	// Initialize attributes

	D3DXMatrixIdentity(&world);
	D3DXMatrixIdentity(&rotationMatrix);
	D3DXMatrixIdentity(&translationMatrix);
	D3DXMatrixIdentity(&scaleMatrix);

	currentRotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	currentPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

}
void Base::SetRotation(D3DXVECTOR3 input){

	currentRotation = input;

	D3DXMATRIX xRot;
	D3DXMATRIX yRot;
	D3DXMATRIX zRot;

	D3DXMatrixRotationX(&xRot, currentRotation.x);
	D3DXMatrixRotationY(&yRot, currentRotation.y);
	D3DXMatrixRotationZ(&zRot, currentRotation.z);

	rotationMatrix = xRot * yRot * zRot;

}
void Base::SetPosition(D3DXVECTOR3 pos){
	currentPosition = pos;
	D3DXMatrixTranslation(&translationMatrix, currentPosition.x, currentPosition.y, currentPosition.z);
}

void Base::SetScale(D3DXVECTOR3 scale) {
	currentScale = scale;
	D3DXMatrixScaling(&scaleMatrix, currentScale.x, currentScale.y, currentScale.z);
}

D3DXMATRIX Base::GetMatrix(){
	return world;
}
D3DXVECTOR3 Base::GetPosition(){
	return currentPosition;
}

void Base::TranslatePosition(D3DXVECTOR3 pos){
	currentPosition += pos;
	D3DXMatrixTranslation(&translationMatrix, currentPosition.x, currentPosition.y, currentPosition.z);
}

Base::~Base(){
}

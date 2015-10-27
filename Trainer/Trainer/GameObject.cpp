#include "GameObject.h"


GameObject::GameObject(float r, float g, float b) {
	colourRGB = D3DXVECTOR3(r, g, b);
}
void GameObject::Draw(DrawObjectSettings* settings) {

	D3DXMatrixIdentity(&world);

	world *= scaleMatrix * rotationMatrix * translationMatrix;
	WVP = world * settings->viewProjection;

	D3DXMatrixTranspose(&settings->constantBuffer->WVP, &WVP); // Send WVP to constant buffer
	D3DXMatrixTranspose(&settings->constantBuffer->world, &world);
	settings->constantBuffer->colour = colourRGB;

	settings->devCon->UpdateSubresource(settings->devConstantBuffer, 0, NULL, settings->constantBuffer, 0, 0);
	settings->devCon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	settings->devCon->DrawIndexed(36, 0, 0);

}

void GameObject::Draw(ID3D11DeviceContext* devCon, ID3D11Buffer* devConstantBuffer, ObjectConstantBuffer* constantBuffer, D3DXMATRIX viewProjection) {

	D3DXMatrixIdentity(&world);

	world *= scaleMatrix * rotationMatrix * translationMatrix;
	WVP = world * viewProjection;

	D3DXMatrixTranspose(&constantBuffer->WVP, &WVP); // Send WVP to constant buffer
	D3DXMatrixTranspose(&constantBuffer->world, &world);
	constantBuffer->colour = colourRGB;

	devCon->UpdateSubresource(devConstantBuffer, 0, NULL, constantBuffer, 0, 0);

	devCon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	devCon->DrawIndexed(36, 0, 0);

}

void GameObject::Update(float dt) {

}
void GameObject::CleanUp() {

}
GameObject::~GameObject() {
	CleanUp();
}

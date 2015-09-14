#pragma once

#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>

struct Light
{
	Light() {
		ZeroMemory(this, sizeof(Light));
	}

	D3DXVECTOR4 pos;
	D3DXVECTOR4 dir;
	D3DXVECTOR4 amb;
	D3DXVECTOR4 dif;
	D3DXVECTOR4 att;
	float range;
};

struct ObjectConstantBuffer{
	D3DXMATRIX WVP;
	D3DXMATRIX world;
	D3DXVECTOR3 colour;
};

struct FrameConstantBuffer {
	Light light;
};
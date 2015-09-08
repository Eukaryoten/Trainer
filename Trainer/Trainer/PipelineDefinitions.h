#pragma once

#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>

struct Light
{
	Light() {
		ZeroMemory(this, sizeof(Light));
	}
	D3DXVECTOR4 dir;
	D3DXVECTOR4 ambient;
	D3DXVECTOR4 diffuse;
};

struct ObjectConstantBuffer{
	D3DXMATRIX WVP;
	D3DXMATRIX world;
};

struct FrameConstantBuffer {
	Light light;
};
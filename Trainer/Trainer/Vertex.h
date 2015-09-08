#pragma once
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>


namespace Vertex
{
	struct Position{
		Position(){}
		Position(
			float x, float y, float z,
			float u, float v, float w,
			float nx, float ny, float nz)
			: pos(x, y, z),
			  tex(u, v, w),
			  nor(nx, ny, nz){}

		Position(
			D3DXVECTOR3 pos,
			D3DXVECTOR3 tex,
			D3DXVECTOR3 nor)
			:
			pos(pos),
			tex(tex),
			nor(nor){}

		D3DXVECTOR3 pos;
		D3DXVECTOR3 tex;
		D3DXVECTOR3 nor;
	};
}

class InputLayoutDesc
{
public:
	static const D3D11_INPUT_ELEMENT_DESC inputLayout[3];
};

class InputLayouts
{
public:
	static void CleanUp();
	static ID3D11InputLayout* inputLayout;
};




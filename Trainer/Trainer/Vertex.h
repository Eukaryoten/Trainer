#pragma once
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>


namespace Vertex
{

	enum LayoutType { PositionLayout, TexturedLayout, NormalLayout, CompleteLayout
	};

	struct Complete{
		Complete(){}
		Complete(
			float x, float y, float z,
			float u, float v, float w,
			float nx, float ny, float nz)
			: pos(x, y, z),
			  tex(u, v, w),
			  nor(nx, ny, nz){}

		Complete(
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

	struct Normals {
		Normals() {}
		Normals(
			float x, float y, float z,
			float nx, float ny, float nz)
			: pos(x, y, z),
			nor(nx, ny, nz) {}

		Normals(
			D3DXVECTOR3 pos,
			D3DXVECTOR3 nor)
			:
			pos(pos),
			nor(nor) {}

		D3DXVECTOR3 pos;
		D3DXVECTOR3 nor;
	};


}

class InputLayoutDesc
{
public:
	static const D3D11_INPUT_ELEMENT_DESC positionLayout[1];
	static const D3D11_INPUT_ELEMENT_DESC texturedLayout[2];
	static const D3D11_INPUT_ELEMENT_DESC normalsLayout [2];
	static const D3D11_INPUT_ELEMENT_DESC completeLayout[3];
};




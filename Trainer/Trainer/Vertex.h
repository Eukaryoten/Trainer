#pragma once
#include "PipelineDefinitions.h"
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>


namespace Vertex
{

	enum LayoutType { PositionLayout, ColouredLayout, TexturedLayout, NormalLayout, ColouredNormalLayout, TexturedNormalLayout};

	struct Position {
		Position() {}
		Position(
			float x, float y, float z)
			: pos(x, y, z){}

		Position(
			D3DXVECTOR3 pos)
			:
			pos(pos) {}

		D3DXVECTOR3 pos;
	};

	struct Coloured {
		Coloured() {}
		Coloured(
			float x, float y, float z,
			float r, float g, float b)
			: pos(x, y, z),
			col(r, g, b) {}

		Coloured(
			D3DXVECTOR3 pos,
			D3DXVECTOR3 col)
			:
			pos(pos),
			col(col) {}

		D3DXVECTOR3 pos;
		D3DXVECTOR3 col;
	};

	struct Textured {
		Textured() {}
		Textured(
			float x, float y, float z,
			float u, float v, float w)
			: pos(x, y, z),
			  tex(u, v, w) {}

		Textured(
			D3DXVECTOR3 pos,
			D3DXVECTOR3 tex)
			:
			pos(pos),
			tex(tex) {}

		D3DXVECTOR3 pos;
		D3DXVECTOR3 tex;
	};



	struct Normal {
		Normal() {}
		Normal(
			float x, float y, float z,
			float nx, float ny, float nz)
			: pos(x, y, z),
			nor(nx, ny, nz) {}

		Normal(
			D3DXVECTOR3 pos,
			D3DXVECTOR3 nor)
			:
			pos(pos),
			nor(nor) {}

		D3DXVECTOR3 pos;
		D3DXVECTOR3 nor;
	};

	struct ColouredNormal {
		ColouredNormal() {}
		ColouredNormal(
			float x, float y, float z,
			float r, float g, float b,
			float nx, float ny, float nz)
			: pos(x, y, z),
			  col(r,g,b),
			  nor(nx, ny, nz)
			  {}

		ColouredNormal(
			D3DXVECTOR3 pos,
			D3DXVECTOR3 col,
			D3DXVECTOR3 nor)
			:
			pos(pos),
			col(col),
			nor(nor) {}

		D3DXVECTOR3 pos;
		D3DXVECTOR3 col;
		D3DXVECTOR3 nor;
	};

	struct TexturedNormal {
		TexturedNormal() {}
		TexturedNormal(
			float x, float y, float z,
			float u, float v, float w,
			float nx, float ny, float nz)
			: pos(x, y, z),
			tex(u, v, w),
			nor(nx, ny, nz) {}

		TexturedNormal(
			D3DXVECTOR3 pos,
			D3DXVECTOR3 tex,
			D3DXVECTOR3 nor)
			:
			pos(pos),
			tex(tex),
			nor(nor) {}

		D3DXVECTOR3 pos;
		D3DXVECTOR3 tex;
		D3DXVECTOR3 nor;
	};


}

class InputLayoutDesc
{
public:
	static const D3D11_INPUT_ELEMENT_DESC positionLayout	  [1];
	static const D3D11_INPUT_ELEMENT_DESC colouredLayout	  [2];
	static const D3D11_INPUT_ELEMENT_DESC texturedLayout	  [2];
	static const D3D11_INPUT_ELEMENT_DESC normalLayout		  [2];
	static const D3D11_INPUT_ELEMENT_DESC colouredNormalLayout[3];
	static const D3D11_INPUT_ELEMENT_DESC texturedNormalLayout[3];
};




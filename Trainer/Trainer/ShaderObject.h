#pragma once

#include "Vertex.h"

class ShaderObject
{
public:
	ShaderObject(ID3D11Device *dev, LPCTSTR shaderSourceFile, Vertex::LayoutType layout);
	void SetShaderObject(ID3D11DeviceContext *devCon);

	~ShaderObject();

private:

	ID3D11InputLayout *inputLayout;
	ID3D10Blob *vsBlob;
	ID3D10Blob *psBlob;
	ID3D11VertexShader *vertexShader;
	ID3D11PixelShader  *pixelShader;
	ID3D11SamplerState *samplerState;
};


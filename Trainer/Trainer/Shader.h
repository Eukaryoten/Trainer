#pragma once
#include "Vertex.h"

class Shader
{
public:
	Shader(ID3D11Device *dev, LPCTSTR shaderSourceFile);
	void SetAsCurrentShader(ID3D11DeviceContext *devCon);
	void SetInputLayout(ID3D11Device *dev);

	~Shader();

private:

	ID3D10Blob *vsBlob;
	ID3D10Blob *psBlob;
	ID3D11InputLayout *inputLayout;
	ID3D11VertexShader *vertexShader;
	ID3D11PixelShader  *pixelShader;
	ID3D11SamplerState *samplerState;
};


#include "ShaderObject.h"


ShaderObject::ShaderObject(ID3D11Device *dev, LPCTSTR shaderSourceFile, Vertex::LayoutType layout) {

	D3DX11CompileFromFile(shaderSourceFile, 0, 0, "VS", "vs_5_0", 0, 0, 0, &vsBlob, 0, 0); // Vertex ShaderObject Stage
	D3DX11CompileFromFile(shaderSourceFile, 0, 0, "PS", "ps_5_0", 0, 0, 0, &psBlob, 0, 0); // Pixel ShaderObject Stage

	dev->CreateVertexShader(vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), NULL, &vertexShader);
	dev->CreatePixelShader(psBlob->GetBufferPointer(), psBlob->GetBufferSize(), NULL, &pixelShader);

	switch (layout) {
	case Vertex::PositionLayout:
		dev->CreateInputLayout(InputLayoutDesc::positionLayout, 1, vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), &inputLayout);
		break;
	case Vertex::ColouredLayout:
		dev->CreateInputLayout(InputLayoutDesc::colouredLayout, 2, vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), &inputLayout);
		break;
	case Vertex::TexturedLayout:
		dev->CreateInputLayout(InputLayoutDesc::texturedLayout, 2, vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), &inputLayout);
		break;
	case Vertex::NormalLayout:
		dev->CreateInputLayout(InputLayoutDesc::normalLayout, 2, vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), &inputLayout);
		break;
	case Vertex::ColouredNormalLayout:
		dev->CreateInputLayout(InputLayoutDesc::colouredNormalLayout, 3, vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), &inputLayout);
		break;
	case Vertex::TexturedNormalLayout:
		dev->CreateInputLayout(InputLayoutDesc::texturedNormalLayout, 3, vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), &inputLayout);
		break;
	}

}

void ShaderObject::SetShaderObject(ID3D11DeviceContext *devCon) {
	devCon->VSSetShader(vertexShader, 0, 0);
	devCon->PSSetShader(pixelShader, 0, 0);
	devCon->IASetInputLayout(inputLayout);
}

ShaderObject::~ShaderObject() {
	inputLayout->Release();
	vsBlob->Release();
	psBlob->Release();
	vertexShader->Release();
	pixelShader->Release();
}

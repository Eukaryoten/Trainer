#include "Shader.h"


Shader::Shader(ID3D11Device *dev, LPCTSTR shaderSourceFile) {

	D3DX11CompileFromFile(shaderSourceFile, 0, 0, "VS", "vs_5_0", 0, 0, 0, &vsBlob, 0, 0); // Vertex Shader Stage
	D3DX11CompileFromFile(shaderSourceFile, 0, 0, "PS", "ps_5_0", 0, 0, 0, &psBlob, 0, 0); // Pixel Shader Stage

	dev->CreateVertexShader(vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), NULL, &vertexShader);
	dev->CreatePixelShader(psBlob->GetBufferPointer(), psBlob->GetBufferSize(), NULL, &pixelShader);

	SetInputLayout(dev);

}

void Shader::SetAsCurrentShader(ID3D11DeviceContext *devCon) {
	devCon->VSSetShader(vertexShader, 0, 0);
	devCon->PSSetShader(pixelShader, 0, 0);
	devCon->IASetInputLayout(inputLayout);
}

void Shader::SetInputLayout(ID3D11Device *dev) {
	dev->CreateInputLayout(InputLayoutDesc::inputLayout, 2, vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), &inputLayout);
}



Shader::~Shader() {
	vsBlob->Release();
	psBlob->Release();
	vertexShader->Release();
	pixelShader->Release();
}

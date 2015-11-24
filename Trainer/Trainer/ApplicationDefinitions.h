#pragma once
#include "WindowDefinitions.h"
#include "PipelineDefinitions.h"


struct DrawObjectSettings {

	DrawObjectSettings(){}

	ID3D11DeviceContext* devCon;
	ID3D11Buffer* devConstantBuffer;
	ObjectConstantBuffer* constantBuffer;
	D3DXMATRIX viewProjection;

};

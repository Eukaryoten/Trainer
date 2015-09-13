#include "GeometryManager.h"


GeometryManager::GeometryManager() {

}

GeometryManager::GeometryManager(ID3D11Device *dev, Vertex::LayoutType layout){

	layoutType = layout;

	tempCubeDim.x = 1;
	tempCubeDim.y = 1;
	tempCubeDim.z = 1;

	cubeVertexCount = 24;
	cubeIndexCount = 36;

	switch (layout) {
	case Vertex::PositionLayout:
		stride = sizeof(Vertex::Position);
		break;
	case Vertex::ColouredLayout:
		stride = sizeof(Vertex::Coloured);
		break;
	case Vertex::TexturedLayout:
		stride = sizeof(Vertex::Textured);
		break;
	case Vertex::NormalLayout:
		stride = sizeof(Vertex::Normal);
		break;
	case Vertex::ColouredNormalLayout:
		stride = sizeof(Vertex::ColouredNormal);
		break;
	case Vertex::TexturedNormalLayout:
		stride = sizeof(Vertex::TexturedNormal);
		break;
	}

	offset = 0;

}


void GeometryManager::LoadData(){

	AddCubeVertexData();
	AddCubeIndexData();

}

void GeometryManager::LoadVertexBuffer(ID3D11Device *dev){

	D3D11_BUFFER_DESC vertexBufferDesc;

	ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	switch (layoutType) {
	case Vertex::PositionLayout:
		vertexBufferDesc.ByteWidth = sizeof(Vertex::Position) * positionData.size();
		break;
	case Vertex::ColouredLayout:
		vertexBufferDesc.ByteWidth = sizeof(Vertex::Coloured) * colouredData.size();
		break;
	case Vertex::TexturedLayout:
		vertexBufferDesc.ByteWidth = sizeof(Vertex::Textured) * texturedData.size();
		break;
	case Vertex::NormalLayout:
		vertexBufferDesc.ByteWidth = sizeof(Vertex::Normal) * normalData.size();
		break;
	case Vertex::ColouredNormalLayout:
		vertexBufferDesc.ByteWidth = sizeof(Vertex::ColouredNormal) * colouredNormalData.size();
		break;
	case Vertex::TexturedNormalLayout:
		vertexBufferDesc.ByteWidth = sizeof(Vertex::TexturedNormal) * texturedNormalData.size();
		break;
	}

	vertexBufferDesc.ByteWidth = sizeof(Vertex::ColouredNormal) * vertexData.size();

	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA vertexBufferData;

	ZeroMemory(&vertexBufferData, sizeof(vertexBufferData));
	vertexBufferData.pSysMem = GetVertexData();

	dev->CreateBuffer(&vertexBufferDesc, &vertexBufferData, &vertexBuffer);

}
void GeometryManager::LoadIndexBuffer(ID3D11Device *dev){

	D3D11_BUFFER_DESC indexBufferDesc;
	ZeroMemory(&indexBufferDesc, sizeof(indexBufferDesc));
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(DWORD) * indexData.size();
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA indexBufferData;
	indexBufferData.pSysMem = GetIndexData();

	dev->CreateBuffer(&indexBufferDesc, &indexBufferData, &indexBuffer);

}

Vertex::ColouredNormal* GeometryManager::GetVertexData(){

	Vertex::ColouredNormal* output = new Vertex::ColouredNormal[vertexData.size()];

	for (int i = 0; i < vertexData.size(); i++){
		output[i] = vertexData[i];
	}

	return output;

}

DWORD* GeometryManager::GetIndexData(){

	DWORD* output = new DWORD[indexData.size()];

	for (int i = 0; i < indexData.size(); i++){
		output[i] = indexData[i];
	}

	return output;

}

void GeometryManager::AddCubeVertexData(){

	Vertex::ColouredNormal *tempArray = new Vertex::ColouredNormal[cubeVertexCount];

	// Front Face

	tempArray[0]  = Vertex::ColouredNormal(-1.0f, -1.0f, -1.0f, 1.0, 0.0, 1.0, -1.0f, -1.0f, -1.0f);
	tempArray[1]  = Vertex::ColouredNormal(-1.0f,  1.0f, -1.0f, 1.0, 0.0, 1.0, -1.0f,  1.0f, -1.0f);
	tempArray[2]  = Vertex::ColouredNormal( 1.0f,  1.0f, -1.0f, 1.0, 0.0, 1.0,  1.0f,  1.0f, -1.0f);
	tempArray[3]  = Vertex::ColouredNormal( 1.0f, -1.0f, -1.0f, 1.0, 0.0, 1.0,  1.0f, -1.0f, -1.0f);

		// Back Face

	tempArray[4]  = Vertex::ColouredNormal(-1.0f, -1.0f, 1.0f, 1.0, 0.0, 1.0, -1.0f, -1.0f, 1.0f);
	tempArray[5]  = Vertex::ColouredNormal( 1.0f, -1.0f, 1.0f, 1.0, 0.0, 1.0,  1.0f, -1.0f, 1.0f);
	tempArray[6]  = Vertex::ColouredNormal( 1.0f,  1.0f, 1.0f, 1.0, 0.0, 1.0,  1.0f,  1.0f, 1.0f);
	tempArray[7]  = Vertex::ColouredNormal(-1.0f,  1.0f, 1.0f, 1.0, 0.0, 1.0, -1.0f,  1.0f, 1.0f);

		// Top Face
	tempArray[8]  = Vertex::ColouredNormal(-1.0f, 1.0f, -1.0f,  0.0, 1.0, 1.0, -1.0f, 1.0f, -1.0f);
	tempArray[9]  = Vertex::ColouredNormal(-1.0f, 1.0f,  1.0f,  1.0, 0.0, 1.0, -1.0f, 1.0f,  1.0f);
	tempArray[10] = Vertex::ColouredNormal( 1.0f, 1.0f,  1.0f,  1.0, 0.0, 1.0,  1.0f, 1.0f,  1.0f);
	tempArray[11] = Vertex::ColouredNormal( 1.0f, 1.0f, -1.0f,  1.0, 0.0, 1.0,  1.0f, 1.0f, -1.0f);

		// Bottom Face
	tempArray[12] = Vertex::ColouredNormal(-1.0f, -1.0f, -1.0f, 1.0, 0.0, 1.0, -1.0f, -1.0f, -1.0f);
	tempArray[13] = Vertex::ColouredNormal( 1.0f, -1.0f, -1.0f, 1.0, 0.0, 1.0,  1.0f, -1.0f, -1.0f);
	tempArray[14] = Vertex::ColouredNormal( 1.0f, -1.0f,  1.0f, 1.0, 0.0, 1.0,  1.0f, -1.0f,  1.0f);
	tempArray[15] = Vertex::ColouredNormal(-1.0f, -1.0f,  1.0f, 1.0, 0.0, 1.0, -1.0f, -1.0f,  1.0f);

		// Left Face
	tempArray[16] = Vertex::ColouredNormal(-1.0f, -1.0f,  1.0f, 1.0, 0.0, 1.0, -1.0f, -1.0f,  1.0f);
	tempArray[17] = Vertex::ColouredNormal(-1.0f,  1.0f,  1.0f, 1.0, 0.0, 1.0, -1.0f,  1.0f,  1.0f);
	tempArray[18] = Vertex::ColouredNormal(-1.0f,  1.0f, -1.0f, 1.0, 0.0, 1.0, -1.0f,  1.0f, -1.0f);
	tempArray[19] = Vertex::ColouredNormal(-1.0f, -1.0f, -1.0f, 1.0, 0.0, 1.0, -1.0f, -1.0f, -1.0f);

		// Right Face
	tempArray[20] = Vertex::ColouredNormal( 1.0f, -1.0f, -1.0f, 0.0, 0.0, 1.0, 1.0f, -1.0f, -1.0f);
	tempArray[21] = Vertex::ColouredNormal( 1.0f,  1.0f, -1.0f, 0.0, 0.0, 1.0, 1.0f,  1.0f, -1.0f);
	tempArray[22] = Vertex::ColouredNormal( 1.0f,  1.0f,  1.0f, 0.0, 0.0, 1.0, 1.0f,  1.0f,  1.0f);
	tempArray[23] = Vertex::ColouredNormal( 1.0f, -1.0f,  1.0f, 0.0, 0.0, 1.0, 1.0f, -1.0f,  1.0f);

	for (int i = 0; i < cubeVertexCount; i++) vertexData.push_back(tempArray[i]);

}
void GeometryManager::AddCubeIndexData(){

	DWORD *tempArray = new DWORD[cubeIndexCount];

	tempArray[0] = 0;
	tempArray[1] = 1;
	tempArray[2] = 2;
	tempArray[3] = 0;
	tempArray[4] = 2;
	tempArray[5] = 3;

	tempArray[6] = 4;
	tempArray[7] = 5;
	tempArray[8] = 6;
	tempArray[9] = 4;
	tempArray[10] = 6;
	tempArray[11] = 7;

	tempArray[12] = 8;
	tempArray[13] = 9;
	tempArray[14] = 10;
	tempArray[15] = 8;
	tempArray[16] = 10;
	tempArray[17] = 11;

	tempArray[18] = 12;
	tempArray[19] = 13;
	tempArray[20] = 14;
	tempArray[21] = 12;
	tempArray[22] = 14;
	tempArray[23] = 15;

	tempArray[24] = 16;
	tempArray[25] = 17;
	tempArray[26] = 18;
	tempArray[27] = 16;
	tempArray[28] = 18;
	tempArray[29] = 19;

	tempArray[30] = 20;
	tempArray[31] = 21;
	tempArray[32] = 22;
	tempArray[33] = 20;
	tempArray[34] = 22;
	tempArray[35] = 23;

	for (int i = 0; i < cubeIndexCount; i++) indexData.push_back(tempArray[i]);

}

void GeometryManager::SetVertexBuffer(ID3D11DeviceContext *devCon){
	devCon->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
}
void GeometryManager::SetIndexBuffer(ID3D11DeviceContext *devCon){
	devCon->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
}


GeometryManager::~GeometryManager(){
}

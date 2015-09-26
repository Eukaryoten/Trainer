#pragma once

#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>
#include <vector>

#include "Vertex.h"

template <class Layout>class GeometryManager
{
public:
	GeometryManager();

	void Initialize(ID3D11Device *dev, ID3D11DeviceContext *devCon);

	void LoadData();
	void LoadVertexBuffer(ID3D11Device *dev);
	void LoadIndexBuffer(ID3D11Device *dev);

	void AddCubeVertexData();
	void AddCubeIndexData();

	void AddSphereVertexData(float radius, float lati, float longi);
	void AddSphereIndexData(float radius, float lati, float longi);

	void SetVertexBuffer(ID3D11DeviceContext *devCon);
	void SetIndexBuffer(ID3D11DeviceContext *devCon);

	Layout* GetVertexData();
	DWORD* GetIndexData();

	~GeometryManager();

private:

	D3DXVECTOR3 tempCubeDim;

	std::vector<Layout>vertexData;
	std::vector<DWORD>indexData;

	float xScale;
	float yScale;
	float zScale;
	UINT stride;
	UINT offset;

	ID3D11Buffer *vertexBuffer;
	ID3D11Buffer *indexBuffer;

	int cubeVertexCount;
	int cubeIndexCount;
};

template <class Layout>
GeometryManager<Layout>::GeometryManager() {

	tempCubeDim.x = 1;
	tempCubeDim.y = 1;
	tempCubeDim.z = 1;

	cubeVertexCount = 24;
	cubeIndexCount = 36;

	stride = sizeof(Layout);
	offset = 0;

}

template <class Layout>
void GeometryManager<Layout>::Initialize(ID3D11Device *dev, ID3D11DeviceContext *devCon) {

	LoadData();
	LoadVertexBuffer(dev);
	LoadIndexBuffer(dev);

	SetVertexBuffer(devCon);
	SetIndexBuffer(devCon);
}

template <class Layout>
void GeometryManager<Layout>::LoadData() {

	AddCubeVertexData();
	AddCubeIndexData();
	AddSphereVertexData(1,20,20);

}

template <class Layout>
void GeometryManager<Layout>::LoadVertexBuffer(ID3D11Device *dev) {

	D3D11_BUFFER_DESC vertexBufferDesc;

	ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	vertexBufferDesc.ByteWidth = sizeof(Layout) * vertexData.size();

	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA vertexBufferData;

	ZeroMemory(&vertexBufferData, sizeof(vertexBufferData));
	vertexBufferData.pSysMem = GetVertexData();

	dev->CreateBuffer(&vertexBufferDesc, &vertexBufferData, &vertexBuffer);

}

template <class Layout>
void GeometryManager<Layout>::LoadIndexBuffer(ID3D11Device *dev) {

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


template <class Layout>
Layout* GeometryManager<Layout>::GetVertexData() {

	Layout* output = new Layout[vertexData.size()];

	for (int i = 0; i < vertexData.size(); i++) {
		output[i] = vertexData[i];
	}

	return output;

}


template <class Layout>
DWORD* GeometryManager<Layout>::GetIndexData() {

	DWORD* output = new DWORD[indexData.size()];

	for (int i = 0; i < indexData.size(); i++) {
		output[i] = indexData[i];
	}

	return output;

}


template <class Layout>
void GeometryManager<Layout>::AddCubeVertexData() {

	Layout *tempArray = new Layout[cubeVertexCount];

	D3DXVECTOR3 *positionData = new D3DXVECTOR3[cubeVertexCount];
	D3DXVECTOR3 *colourData = new D3DXVECTOR3[cubeVertexCount];
	D3DXVECTOR3 *normalData = new D3DXVECTOR3[cubeVertexCount];

	// -------------------------------------------------------------- Position, Normals & Colour --------------------------------------------------------- \\

	positionData[0]  = D3DXVECTOR3(-1.0f, -1.0f, -1.0f); colourData[0]  = D3DXVECTOR3( 1.0f, 0.0f, 0.0f); normalData[0]  = D3DXVECTOR3( 0.0f,  0.0f, -1.0f);
	positionData[1]  = D3DXVECTOR3(-1.0f,  1.0f, -1.0f); colourData[1]  = D3DXVECTOR3( 1.0f, 1.0f, 0.0f); normalData[1]  = D3DXVECTOR3( 0.0f,  0.0f, -1.0f);
	positionData[2]  = D3DXVECTOR3( 1.0f,  1.0f, -1.0f); colourData[2]  = D3DXVECTOR3( 1.0f, 0.0f, 0.0f); normalData[2]  = D3DXVECTOR3( 0.0f,  0.0f, -1.0f);
	positionData[3]  = D3DXVECTOR3( 1.0f, -1.0f, -1.0f); colourData[3]  = D3DXVECTOR3( 0.0f, 1.0f, 1.0f); normalData[3]  = D3DXVECTOR3( 0.0f,  0.0f, -1.0f);

	// Back Face

	positionData[4]  = D3DXVECTOR3(-1.0f, -1.0f,  1.0f); colourData[4]  = D3DXVECTOR3( 0.0f, 1.0f, 1.0f); normalData[4]  = D3DXVECTOR3( 0.0f,  0.0f,  1.0f);
	positionData[5]  = D3DXVECTOR3( 1.0f, -1.0f,  1.0f); colourData[5]  = D3DXVECTOR3( 1.0f, 0.0f, 0.0f); normalData[5]  = D3DXVECTOR3( 0.0f,  0.0f,  1.0f);
	positionData[6]  = D3DXVECTOR3( 1.0f,  1.0f,  1.0f); colourData[6]  = D3DXVECTOR3( 0.0f, 1.0f, 1.0f); normalData[6]  = D3DXVECTOR3( 0.0f,  0.0f,  1.0f);
	positionData[7]  = D3DXVECTOR3(-1.0f,  1.0f,  1.0f); colourData[7]  = D3DXVECTOR3( 1.0f, 0.0f, 1.0f); normalData[7]  = D3DXVECTOR3( 0.0f,  0.0f,  1.0f);

	// Top Face
	positionData[8]  = D3DXVECTOR3(-1.0f,  1.0f, -1.0f); colourData[8]  = D3DXVECTOR3( 1.0f, 1.0f, 0.0f); normalData[8]  = D3DXVECTOR3( 0.0f,  1.0f,  0.0f);
	positionData[9]  = D3DXVECTOR3(-1.0f,  1.0f,  1.0f); colourData[9]  = D3DXVECTOR3( 1.0f, 1.0f, 0.0f); normalData[9]  = D3DXVECTOR3( 0.0f,  1.0f,  0.0f);
	positionData[10] = D3DXVECTOR3( 1.0f,  1.0f,  1.0f); colourData[10] = D3DXVECTOR3( 1.0f, 1.0f, 0.0f); normalData[10] = D3DXVECTOR3( 0.0f,  1.0f,  0.0f);
	positionData[11] = D3DXVECTOR3( 1.0f,  1.0f, -1.0f); colourData[11] = D3DXVECTOR3( 1.0f, 1.0f, 0.0f); normalData[11] = D3DXVECTOR3( 0.0f,  1.0f,  0.0f); 

	// Bottom Face
	positionData[12] = D3DXVECTOR3(-1.0f, -1.0f, -1.0f); colourData[12] = D3DXVECTOR3( 1.0f, 1.0f, 0.0f); normalData[12] = D3DXVECTOR3( 0.0f, -1.0f,  0.0f);
	positionData[13] = D3DXVECTOR3( 1.0f, -1.0f, -1.0f); colourData[13] = D3DXVECTOR3( 1.0f, 1.0f, 0.0f); normalData[13] = D3DXVECTOR3( 0.0f, -1.0f,  0.0f); 
	positionData[14] = D3DXVECTOR3( 1.0f, -1.0f,  1.0f); colourData[14] = D3DXVECTOR3( 1.0f, 0.0f, 1.0f); normalData[14] = D3DXVECTOR3( 0.0f, -1.0f,  0.0f); 
	positionData[15] = D3DXVECTOR3(-1.0f, -1.0f,  1.0f); colourData[15] = D3DXVECTOR3( 1.0f, 0.0f, 1.0f); normalData[15] = D3DXVECTOR3( 0.0f, -1.0f,  0.0f);

	// Left Face
	positionData[16] = D3DXVECTOR3(-1.0f, -1.0f,  1.0f); colourData[16] = D3DXVECTOR3( 1.0f, 0.0f, 1.0f); normalData[16] = D3DXVECTOR3( -1.0f, 0.0f,  0.0f); 
	positionData[17] = D3DXVECTOR3(-1.0f,  1.0f,  1.0f); colourData[17] = D3DXVECTOR3( 1.0f, 0.0f, 0.0f); normalData[17] = D3DXVECTOR3( -1.0f, 0.0f,  0.0f);
	positionData[18] = D3DXVECTOR3(-1.0f,  1.0f, -1.0f); colourData[18] = D3DXVECTOR3( 1.0f, 0.0f, 1.0f); normalData[18] = D3DXVECTOR3( -1.0f, 0.0f,  0.0f); 
	positionData[19] = D3DXVECTOR3(-1.0f, -1.0f, -1.0f); colourData[19] = D3DXVECTOR3( 0.0f, 0.0f, 1.0f); normalData[19] = D3DXVECTOR3( -1.0f, 0.0f,  0.0f);

	// Right Face
	positionData[20] = D3DXVECTOR3( 1.0f, -1.0f, -1.0f); colourData[20] = D3DXVECTOR3 (1.0f, 0.0f, 1.0f); normalData[20] = D3DXVECTOR3( 1.0f,  0.0f,  0.0f); 
	positionData[21] = D3DXVECTOR3( 1.0f,  1.0f, -1.0f); colourData[21] = D3DXVECTOR3( 0.0f, 1.0f, 0.0f); normalData[21] = D3DXVECTOR3( 1.0f,  0.0f,  0.0f); 
	positionData[22] = D3DXVECTOR3( 1.0f,  1.0f,  1.0f); colourData[22] = D3DXVECTOR3( 1.0f, 0.0f, 1.0f); normalData[22] = D3DXVECTOR3( 1.0f,  0.0f,  0.0f);
	positionData[23] = D3DXVECTOR3( 1.0f, -1.0f,  1.0f); colourData[23] = D3DXVECTOR3( 1.0f, 0.0f, 0.0f); normalData[23] = D3DXVECTOR3( 1.0f,  0.0f,  0.0f);

	

	for (int i = 0; i < cubeVertexCount; i++) {

		tempArray[i].pos = positionData[i];

	}

	if (sizeof(Layout) == sizeof(Vertex::Normal) || sizeof(Layout) == sizeof(Vertex::ColouredNormal)) {

		for (int i = 0; i < cubeVertexCount; i++)
			tempArray[i].nor = positionData[i];

	}

	 if (sizeof(Layout) == sizeof(Vertex::ColouredNormal)) {

		//for (int i = 0; i < cubeVertexCount; i++)
			//tempArray[i].col = colourData[i];

	} 

	// -------------------------------------------------------------- Old --------------------------------------------------------- \\


	for (int i = 0; i < cubeVertexCount; i++) vertexData.push_back(tempArray[i]);

}

template <class Layout>
void GeometryManager<Layout>::AddCubeIndexData() {

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

template <class Layout>
void GeometryManager<Layout>::AddSphereVertexData(float radius, float lati, float longi) {

	float M_PI = 3.14;

	for (float latNumber = 0; latNumber <= lati; latNumber++) {

		float theta = latNumber * M_PI / lati;
		float sinTheta = sin(theta);
		float cosTheta = cos(theta);

		for (float longNumber = 0; longNumber <= longi; longNumber++) {
			float phi = longNumber * 2 * M_PI / longi;
			float sinPhi = sin(phi);
			float cosPhi = cos(phi);

			Layout vertex;

			vertex.nor = D3DXVECTOR3(cosPhi * sinTheta, cosTheta, sinPhi * sinTheta);
			vertex.col = D3DXVECTOR3(1.0,0.0,1.0);
			vertex.pos = D3DXVECTOR3(radius * vertex.nor.x, radius * vertex.nor.y, radius * vertex.nor.z);

			vertexData.push_back(vertex);
		}
	}
		

}

template <class Layout>
void GeometryManager<Layout>::AddSphereIndexData(float radius, float lati, float longi) {

}

template <class Layout>
void GeometryManager<Layout>::SetVertexBuffer(ID3D11DeviceContext *devCon) {
	devCon->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
}

template <class Layout>
void GeometryManager<Layout>::SetIndexBuffer(ID3D11DeviceContext *devCon) {
	devCon->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
}

template <class Layout>
GeometryManager<Layout>::~GeometryManager() {
}


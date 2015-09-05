#pragma once

#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

#include "Compile.h"
#include "ModelObject.h"
#include "Vertex.h"

class GeometryManager
{
public:
	GeometryManager();

	void LoadData();

	void LoadVertexBuffer(ID3D11Device *dev);
	void LoadIndexBuffer(ID3D11Device *dev);

	void AddCubeVertexData();
	void AddCubeIndexData();

	void SetVertexBuffer(ID3D11DeviceContext *devCon);
	void SetIndexBuffer(ID3D11DeviceContext *devCon);


	Vertex::Position* GetVertexData();
	DWORD* GetIndexData();

	~GeometryManager();

private:

	D3DXVECTOR3 tempCubeDim;

	std::vector<Vertex::Position>vertexData;
	std::vector<DWORD>indexData;

	std::vector<ModelObject*>modelData;

	float xScale;
	float yScale;
	float zScale;
	UINT stride = sizeof(Vertex::Position);
	UINT offset = 0;
	ID3D11Buffer *vertexBuffer;
	ID3D11Buffer *indexBuffer;

	int cubeVertexCount;
	int cubeIndexCount;
};


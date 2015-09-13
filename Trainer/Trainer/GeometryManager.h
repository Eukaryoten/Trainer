#pragma once

#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>
#include <vector>

#include "Vertex.h"

class GeometryManager
{
public:

	GeometryManager();
	GeometryManager(ID3D11Device *dev, Vertex::LayoutType type);

	void LoadData();

	void LoadVertexBuffer(ID3D11Device *dev);
	void LoadIndexBuffer(ID3D11Device *dev);

	void AddCubeVertexData();
	void AddCubeIndexData();

	void SetVertexBuffer(ID3D11DeviceContext *devCon);
	void SetIndexBuffer(ID3D11DeviceContext *devCon);

	Vertex::ColouredNormal* GetVertexData();

	DWORD* GetIndexData();

	~GeometryManager();

private:

	Vertex::LayoutType layoutType;

	D3DXVECTOR3 tempCubeDim;

	std::vector<Vertex::Position>positionData;
	std::vector<Vertex::Coloured>colouredData;
	std::vector<Vertex::Textured>texturedData;
	std::vector<Vertex::Normal>normalData;
	std::vector<Vertex::ColouredNormal>colouredNormalData;
	std::vector<Vertex::TexturedNormal>texturedNormalData;

	std::vector<Vertex::ColouredNormal>vertexData;


	std::vector<DWORD>indexData;

	//std::vector<ModelObject*>modelData;

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


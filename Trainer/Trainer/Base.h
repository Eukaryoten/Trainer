#pragma once

#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>
#include "PipelineDefinitions.h"

class Base
{
public:

	Base(); // Constructor

	void SetRotation(D3DXVECTOR3); // Sets the rotation vector used to transform the objects matrix
	void SetPosition(D3DXVECTOR3); // Sets the currentPosition attribute by a vector argument
	void SetScale(D3DXVECTOR3);
	void TranslatePosition(D3DXVECTOR3); // Increments the currentPosition attribute by vector argument
	void OffsetAxis(D3DXVECTOR3);

	D3DXMATRIX GetMatrix(); // Returns the objects local matrix
	D3DXVECTOR3 GetPosition(); // Returns the attribute currentPosition which is the centre of the object

	virtual void CleanUp() = 0; // Pure virtual function rendering this abstract - helper to make sure memory is de-allocated
	virtual ~Base(); // Destructor

protected:

	// Matrices

	D3DXMATRIX WVP; // World Matrix * View Matrix * Projection Matrix - Helper attribute which is used to transform object into camera space
	D3DXMATRIX world; // Objects matrix in world space
	D3DXMATRIX viewProjection; // Another helper matrix 
	D3DXMATRIX scaleMatrix; // Used to scale object
	D3DXMATRIX rotationMatrix; // Used to rotate object
	D3DXMATRIX translationMatrix; // Used to translate object

	// Scalars

	D3DXVECTOR3 defaultForward; // Forward in terms of game world orientation
	D3DXVECTOR3 defaultUp; // Up in terms of game world orientation
	D3DXVECTOR3 defaultRight; // Right in terms of game world orientation

	D3DXVECTOR3 currentRotation; // Defines and offset orientation of the object
	D3DXVECTOR3 currentPosition; // Defines the objects current position
	D3DXVECTOR3 currentRight; // Indicates what direction is right
	D3DXVECTOR3 currentUp; // Indicates what direction is up
	D3DXVECTOR3 currentForward; // Indicates what direction is forward
	D3DXVECTOR3 currentScale;
	D3DXVECTOR3 axisOffset;

};


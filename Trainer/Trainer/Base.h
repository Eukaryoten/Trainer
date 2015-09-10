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
	void TranslatePosition(D3DXVECTOR3); // Increments the currentPosition attribute by vector argument

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

	D3DXVECTOR3 currentRotation; // Defines and offset orientation of the object
	D3DXVECTOR3 currentPosition; // Defines the objects current position

};


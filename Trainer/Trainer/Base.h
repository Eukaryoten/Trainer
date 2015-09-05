#pragma once
#include "Compile.h"
class Base
{
public:

	Base(); // Constructor

#pragma region Set Functions

	void SetRotationVector(D3DXVECTOR3); // Sets the rotation vector used to transform the objects matrix
	void SetCurrentForward(D3DXVECTOR3); // Sets the vector which points forward relative to the object
	void SetCurrentRight(D3DXVECTOR3); // Sets the vector which points right relative to the object
	void SetPosition(D3DXVECTOR3); // Sets the currentPosition attribute by a vector argument
	void SetLeftRightSpeed(float speed); // Used to translate Geometry Left/Right depending on relative normalized right vector
	void SetBackForwardSpeed(float speed); // Used to translate Geometry Forwards/Backwards depending on relative Normalized Forward vector

#pragma endregion

#pragma region Get Functions

	D3DXMATRIX GetMatrix(); // Returns the objects local matrix
	D3DXVECTOR3 GetFacingVector(); // Returns the vector which indicates which way is forward relative to object
	D3DXVECTOR3 GetRightVector(); // Returns the vector which indicates which was is right relative to object
	D3DXVECTOR3 GetPosition(); // Returns the attribute currentPosition which is the centre of the object
	void GetPosition(D3DXVECTOR3&); // Alternative function to store currentPosition into referenced variable

#pragma endregion

#pragma region Update Functions

	void UpdateMatrices(); // Stores the matrices in the constant buffer structure which send information to the current shader
	virtual void UpdateGeometry(); // Stores instance position data to be sent to the current shader

#pragma endregion

#pragma region Increment Functions

	void TranslateCurrentPosition(D3DXVECTOR3); // Increments the currentPosition attribute by vector argument

#pragma endregion

	virtual void CleanUp() = 0; // Pure virtual function rendering this abstract - helper to make sure memory is de-allocated
	virtual ~Base(); // Destructor

protected:

	ObjectConstantBuffer* constantBuffer; // Pointer to constant buffer object used to send information to shaders

	// Direction Vectors

	D3DXVECTOR3 currentRight; // Indicates what direction is right
	D3DXVECTOR3 currentUp; // Indicates what direction is up
	D3DXVECTOR3 currentForward; // Indicates what direction is forward
	D3DXVECTOR3 currentPosition; // Centre point of object
	D3DXVECTOR3 defaultForward; // Forward in terms of game world orientation
	D3DXVECTOR3 defaultUp; // Up in terms of game world orientation
	D3DXVECTOR3 defaultRight; // Right in terms of game world orientation

	// Matrices

	D3DXMATRIX WVP; // World Matrix * View Matrix * Projection Matrix - Helper attribute which is used to transform object into camera space
	D3DXMATRIX world; // Objects matrix in world space
	D3DXMATRIX viewProjection; // Another helper matrix 
	D3DXMATRIX scaleMatrix; // Used to scale object
	D3DXMATRIX rotationMatrix; // Used to rotate object
	D3DXMATRIX translationMatrix; // Used to translate object

	// Scalars

	float moveLeftRight; // Offset in Right facing vector
	float moveBackForward; // Offset in Forward facing vector
	D3DXVECTOR3 currentRotation; // Defines and offset orientation of the object
	D3DXVECTOR3 dimension; // Vector containing the width, height and depth information of the object

};


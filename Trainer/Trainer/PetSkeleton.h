#pragma once

#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>

class PetSkeleton
{
public:
	PetSkeleton();
	~PetSkeleton();
private:
	D3DXVECTOR3 head;
	D3DXVECTOR3 tail;
	D3DXVECTOR3 mid;

};


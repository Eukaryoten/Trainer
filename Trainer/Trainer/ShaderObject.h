#pragma once
#include "Compile.h"

class ShaderObject
{
public:
	ShaderObject();
	~ShaderObject();
private:
	ID3D10Blob *vsBlob;
	ID3D10Blob *psBlob;

};


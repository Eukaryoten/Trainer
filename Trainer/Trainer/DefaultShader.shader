cbuffer ObjectConstantBuffer {
	float4x4 WVP;
	float4x4 world;
};

struct Light {
	float4 dir;
	float4 amb;
	float4 dif;
};

cbuffer FrameConstantBuffer {

	Light light;

};

struct VS_INPUT {
	float4 pos	  : POSITION;
	//float3 tex    : TEXCOORD;
	float3 normal : NORMAL;
};

struct VS_OUTPUT {
	float4 pos	  : SV_POSITION;
	//float3 tex    : TEXCOORD;
	float3 normal : NORMAL;
};

VS_OUTPUT VS(VS_INPUT input) { // Vertex shader stage

	VS_OUTPUT output;

	output.pos = input.pos;
	output.normal = input.normal;


	float4 finalPosition = mul(output.pos, WVP);
	float4 finalNormal   = mul(output.normal, world);


	output.pos = finalPosition;
	output.normal = finalNormal;

	return output;

}

float4 PS(VS_OUTPUT input) : SV_TARGET{ // Pixel shader stage

	/*input.normal = normalize(input.normal);

	float4 diffuse = ObjTexture.Sample(ObjSamplerState, input.tex);

	float3 finalColor;

	finalColor = diffuse * light.ambient;
	finalColor += saturate(dot(light.dir, input.normal) * light.diffuse * diffuse);

	return float4(finalColor, diffuse.a);*/

	return float4(0.0,0.5,0.5,0.0); //  Need to look here next, normals working sort of
}
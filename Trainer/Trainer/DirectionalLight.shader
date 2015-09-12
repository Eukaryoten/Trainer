cbuffer ObjectConstantBuffer {
	float4x4 WVP;
	float4x4 world;
};

struct Light {
	float4 pos;
	float4 dir;
	float4 amb;
	float4 dif;
	float4 att;
	float range;
};

cbuffer FrameConstantBuffer {

	Light light;
};

struct VS_INPUT {
	float4 pos	  : POSITION;
	float3 normal : NORMAL;
};

struct VS_OUTPUT {
	float4 pos	  : SV_POSITION;
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

	input.normal = normalize(input.normal);

	float4 diffuse = float4(0.0, 0.5, 0.5, 0.0);
	float3 finalColor;

	finalColor = diffuse * light.amb;
	finalColor += saturate(dot(light.dir, input.normal) * light.dif * diffuse);

	return float4(finalColor, diffuse.a);
}
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
	float3 color  : COLOR;
	float3 normal : NORMAL;
};

struct VS_OUTPUT {
	float4 pos	  : SV_POSITION;
	float3 color  : COLOR;
	float3 normal : NORMAL;
};

VS_OUTPUT VS(VS_INPUT input) { // Vertex shader stage

	VS_OUTPUT output;

	output.pos = mul(input.pos, WVP);
	output.normal = mul(input.normal, world);
	output.color = input.color;

	return output;

}

float4 PS(VS_OUTPUT input) : SV_TARGET{ // Pixel shader stage

	input.normal = normalize(input.normal);

	float4 diffuse = float4(input.color, 0.0);
	float3 finalColor;

	finalColor = diffuse * light.amb;
	finalColor += saturate(dot(light.dir, input.normal) * light.dif * diffuse);

	return float4(finalColor, diffuse.a);
}
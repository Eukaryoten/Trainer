cbuffer ObjectConstantBuffer {
	float4x4 WVP;
	float4x4 world;
};

struct VS_INPUT {
	float4 pos	: POSITION;
	float3 tex  : TEXCOORD;
};

struct VS_OUTPUT {
	float4 pos	: SV_POSITION;
	float3 tex  : TEXCOORD;
};

VS_OUTPUT VS(VS_INPUT input) { // Vertex shader stage

	VS_OUTPUT output;
	output.pos = input.pos;
	float4 finalPosition = mul(output.pos, WVP);
	output.pos = finalPosition;

	return output;

}

float4 PS(VS_OUTPUT input) : SV_TARGET{ // Pixel shader stage

	return float4(0.0,0.5,0.5,0.0);
}
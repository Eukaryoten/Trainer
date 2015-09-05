cbuffer ObjectConstantBuffer{
	float4x4 WVP;
};

struct VS_INPUT{
	float4 pos	: POSITION;
};

struct VS_OUTPUT{
	float4 pos	: SV_POSITION;
};

VS_OUTPUT VS(VS_INPUT input){

    VS_OUTPUT output;

	output.pos = input.pos;
	float4 finalPosition = mul(output.pos, WVP);
	output.pos = finalPosition;

	return output;

}

float4 PS(VS_OUTPUT input) : SV_TARGET {

	return float4(0.5,0.5,0.5,0.0);
}
cbuffer ObjectConstantBuffer {
	float4x4 WVP;
	float4x4 world;
	float3 colour;
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
	float3 color  : COLOR;
	float3 normal : NORMAL;
	float4 world  : POSITION;
};

VS_OUTPUT VS(VS_INPUT input) { // Vertex shader stage

	VS_OUTPUT output;

	output.pos = mul(input.pos,WVP);
	output.world = mul(input.pos, world);
	output.normal = mul(input.normal, world);
	output.color = colour;

	return output;

}

float4 PS(VS_OUTPUT input) : SV_TARGET{ // Pixel shader stage


	//return float4(input.color, 0.0);


	/* Results for light are all zero after changing the code. Possible problems:

	 - Frame constant buffer not being updated properly
	 - Correct light not being passed in
	 - Light is not being assigned to Frame buffer at all
	 
	 */

	float4 diffuse = float4(input.color, 0.0);

	float3 finalColor = float3(0.0f, 0.0f, 0.0f);
	float3 lightToPixelVec = light.pos - input.world;
	float d = length(lightToPixelVec);
	float3 finalAmbient = diffuse * light.amb;


	if (d > light.range) return float4(finalAmbient, diffuse.a);


	lightToPixelVec /= d;
	float howMuchLight = dot(lightToPixelVec, input.normal);


	if (howMuchLight > 0.0f){
	finalColor += howMuchLight * diffuse * light.dif;
	finalColor /= light.att[0] + (light.att[1] * d) + (light.att[2] * (d*d));
	}

	finalColor = saturate(finalColor + finalAmbient);
	return float4(finalColor, diffuse.a);

	
}
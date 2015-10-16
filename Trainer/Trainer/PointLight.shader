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

	//input.normal = normalize(input.normal);

	return float4(input.color, 0.0);

	float4 diffuse = float4(input.color, 0.0);
	float3 finalColor = float3(0.0f, 0.0f, 0.0f);

	//Create the vector between light position and pixels position
	float3 lightToPixelVec = light.pos - input.world;

	//Find the distance between the light pos and pixel pos
	float d = length(lightToPixelVec);

	//Create the ambient light
	float3 finalAmbient = diffuse * light.amb;

	//If pixel is too far, return pixel color with ambient light
	if (d > light.range)
	return float4(finalAmbient, diffuse.a);

	//Turn lightToPixelVec into a unit length vector describing
	//the pixels direction from the lights position
	lightToPixelVec /= d;

	//Calculate how much light the pixel gets by the angle
	//in which the light strikes the pixels surface
	float howMuchLight = dot(lightToPixelVec, input.normal);

	//If light is striking the front side of the pixel
	if (howMuchLight > 0.0f)
	{
	//Add light to the finalColor of the pixel
	finalColor += howMuchLight * diffuse * light.dif;

	//Calculate Light's Falloff factor
	finalColor /= light.att[0] + (light.att[1] * d) + (light.att[2] * (d*d));
	}

	//make sure the values are between 1 and 0, and add the ambient
	finalColor = saturate(finalColor + finalAmbient);

	return float4(finalColor, diffuse.a);
	
}
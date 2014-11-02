struct VS_OUTPUT
{
	float4 Position : SV_Position;
	float3 Normal : NORMAL;
};

cbuffer cbPS : register(b0)
{
	float4 UniformDiffuse;
	float4 CameraPosition;
	float3 LightDirection;
	float Shininess;
	float Ambient;
};

float4 main(VS_OUTPUT In) : SV_Target
{
	float vn = dot(normalize(In.Normal), LightDirection);
	float3 color = max(vn, Ambient) * UniformDiffuse.xyz;
	return float4(color, 1.0f);
}
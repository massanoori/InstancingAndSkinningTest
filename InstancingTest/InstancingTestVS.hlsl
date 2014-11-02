

struct VS_INPUT
{
	float3 Position : POSITION;
	float3 Normal : NORMAL;
	uint4 BlendIndices : BLENDINDICES;
	float4 BlendWeights : BLENDWEIGHT;
	matrix World : INSTANCE_WORLD;
	matrix Transforms[4] : INSTANCE_BONE;
};

struct VS_OUTPUT
{
	float4 Position : SV_Position;
	float3 Normal : NORMAL;
};

cbuffer cbVSPerObject : register(b0)
{
	matrix View;
	matrix Proj;
};

VS_OUTPUT main(in VS_INPUT In)
{
	VS_OUTPUT Out;

	matrix World = mul(
		In.Transforms[In.BlendIndices.x] * In.BlendWeights.x +
		In.Transforms[In.BlendIndices.y] * In.BlendWeights.y +
		In.Transforms[In.BlendIndices.z] * In.BlendWeights.z +
		In.Transforms[In.BlendIndices.w] * In.BlendWeights.w,
		In.World);

	matrix WorldView = mul(World, View);

	Out.Position = mul(mul(float4(In.Position, 1.0f), WorldView), Proj);
	Out.Normal = mul(float4(In.Normal, 0.0f), WorldView).xyz;

	return Out;
}
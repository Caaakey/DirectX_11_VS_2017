cbuffer MatrixBuffer
{
	matrix World;
	matrix View;
	matrix Projection;
};

struct VS_INPUT
{
	float3 Position : POSITION;
	float2 Tex0		: TEXCOORD0;
};

Texture2D texture0;
SamplerState SampleType;

struct PS_INPUT
{
	float4 Position : SV_POSITION;
	float2 Tex0		: TEXCOORD0;
};

PS_INPUT VS(VS_INPUT input)
{
	PS_INPUT output = (PS_INPUT)0;

	output.Position = mul(float4(input.Position, 1), World);
	output.Position = mul(output.Position, View);
	output.Position = mul(output.Position, Projection);
	output.Tex0 = input.Tex0;

	return output;
}

float4 PS(PS_INPUT input) : SV_Target
{
	float4 color = texture0.Sample(SampleType, input.Tex0);
	return color;
}

technique11 Render
{
	pass P0
	{
		SetVertexShader(CompileShader(vs_5_0, VS()));
		SetGeometryShader(NULL);
		SetPixelShader(CompileShader(ps_5_0, PS()));
	}
};
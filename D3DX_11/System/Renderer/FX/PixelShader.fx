cbuffer DefineObject
{
	float4x4 g_MVP;
};

struct IN
{
	float3 Position : POSITION;
	float4 Color	: COLOR;
};

struct OUT
{
	float4 Position : SV_POSITION;
	float4 Color	: COLOR;
};

IN vVertexShader(IN vIn)
{
	OUT vOut;

	vOut.Position = mul(float4(vIn.Position, 1), g_MVP);
	vOut.Color = vIn.Color;
}

float4 vPixelShader(OUT vOut) : SV_TARGET
{
	return vOut.Color;
}

technique Tech
{
	pass PixelPass
	{
		SetVertexShader(CompileShader(vs_5_0, vVertexShader()));
		SetPixelShader(CompileShader(ps_5_0, vPixelShader()));
	}
};
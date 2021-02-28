#pragma once
#include "../DXRenderer.h"

namespace DXShader
{
	struct Vertex
	{
		static const D3D11_INPUT_ELEMENT_DESC Layout[];

		DirectX::XMFLOAT3 Position;
		DirectX::XMFLOAT4 Color;

		static void SetTech(ID3DX11Effect* pEffect, ID3DX11EffectTechnique* pTech, ID3DX11EffectMatrixVariable* pMat)
		{
			pTech = pEffect->GetTechniqueByName("PixelPass");
			pMat = pEffect->GetVariableByName("g_MVP")->AsMatrix();
		}
	};

	const D3D11_INPUT_ELEMENT_DESC Vertex::Layout[] =
	{
		{ "POSITION",	0,	DXGI_FORMAT_R32G32B32_FLOAT,	0,	0,	D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",		0,	DXGI_FORMAT_R32G32B32A32_FLOAT,	0,	12,	D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
}

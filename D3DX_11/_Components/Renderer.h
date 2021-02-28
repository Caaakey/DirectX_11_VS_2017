#pragma once

#pragma comment(lib, "Effects11d.lib")
#include <Dx11Effect/d3dx11effect.h>
#include "System/Renderer/Shader/Vertex.h"

using namespace DXShader;

class Renderer
{
public:
	Renderer();
	~Renderer();

private:
	ID3D11Buffer* m_Vertices;
	ID3D11Buffer* m_Indices;
	UINT m_VerticesCount;
	UINT m_IndicesCount;

	ID3DX11Effect* m_Fx;
	ID3DX11EffectTechnique* m_Techniuque;
	ID3DX11EffectMatrixVariable* m_WorldMat;

	ID3D11InputLayout* m_InputLayout;

public:
	virtual void IASetup(LPCWSTR filePath);
	virtual void IAInputLayout();
};


#include "Renderer.h"
#include "stdafx.h"

Renderer::Renderer()
	: m_Vertices(nullptr), m_Indices(nullptr), m_Fx(nullptr),
	m_VerticesCount(0), m_IndicesCount(0),
	m_Techniuque(nullptr), m_WorldMat(nullptr), 
	m_InputLayout(nullptr)
{
}

Renderer::~Renderer()
{
	SAFE_RELEASE(m_Vertices);
	SAFE_RELEASE(m_Indices);
	SAFE_RELEASE(m_Fx);
	SAFE_RELEASE(m_InputLayout);
}

void Renderer::IASetup(LPCWSTR filePath)
{
	DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS;
	ID3D10Blob* pErrMsg = nullptr;

#if defined _DEBUG
	flags |= D3D10_SHADER_DEBUG;
#endif

	if (FAILED(D3DX11CompileEffectFromFile(
		filePath,
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		flags, 0,
		DXRenderer::Get().GetDevice(),
		&m_Fx,
		&pErrMsg)))
	{
		MessageBox(nullptr, (LPCWSTR)pErrMsg->GetBufferPointer(), L"FX Compile error", MB_OK);
		SAFE_RELEASE(pErrMsg);
		return;
	}

	Vertex::SetTech(m_Fx, m_Techniuque, m_WorldMat);
}

void Renderer::IAInputLayout()
{
	D3D11_INPUT_ELEMENT_DESC elements[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, m_IndicesCount, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	D3DX11_PASS_DESC desc;
	m_Techniuque->GetPassByIndex(0)->GetDesc(&desc);

	if (FAILED(DXRenderer::Get().GetDevice()->CreateInputLayout(elements, 2, desc.pIAInputSignature,
		desc.IAInputSignatureSize, &m_InputLayout)))
	{
		MessageBox(nullptr, L"IAInputLayout error", L"Error", MB_OK);
	}
}

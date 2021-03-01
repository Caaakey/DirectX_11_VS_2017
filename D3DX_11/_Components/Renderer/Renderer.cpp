#include "stdafx.h"
#include "Renderer.h"

namespace Components
{
	Renderer::Renderer(Object* pConnect)
		: Component(pConnect),
		m_Mesh(nullptr),
		m_Vertices(nullptr), m_Indices(nullptr), m_Fx(nullptr),
		m_Techniuque(nullptr),
		m_WorldVariable(nullptr), m_ViewVariable(nullptr), m_ProjectionVariable(nullptr),
		m_InputLayout(nullptr)
	{
	}

	Renderer::~Renderer()
	{
		Release();
	}

	void Renderer::Release()
	{
		SAFE_RELEASE(m_Vertices);
		SAFE_RELEASE(m_Indices);

		SAFE_DELETE(m_Mesh);

		SAFE_RELEASE(m_Fx);
		SAFE_RELEASE(m_InputLayout);
	}

	void Renderer::Update()
	{
	}

	void Renderer::Render()
	{
		DXRenderer::Get().GetContext()->IASetInputLayout(m_InputLayout);
		DXRenderer::Get().GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		UINT stride = sizeof MeshValue::VertexValue;
		UINT offset = 0;

		DXRenderer::Get().GetContext()->IASetVertexBuffers(0, 1, &m_Vertices, &stride, &offset);
		DXRenderer::Get().GetContext()->IASetIndexBuffer(m_Indices, DXGI_FORMAT_R32_UINT, 0);

		DirectX::XMMATRIX world = DirectX::XMMatrixIdentity();

		m_WorldVariable->SetMatrix((float*)&world);
		m_ViewVariable->SetMatrix((float*)&CameraManager::Get().GetViewMatrix());
		m_ProjectionVariable->SetMatrix((float*)&CameraManager::Get().GetProjMatrix());

		D3DX11_TECHNIQUE_DESC techDesc;
		m_Techniuque->GetDesc(&techDesc);

		for (UINT p = 0; p < techDesc.Passes; ++p)
		{
			m_Techniuque->GetPassByIndex(p)->Apply(0, DXRenderer::Get().GetContext());
			DXRenderer::Get().GetContext()->DrawIndexed(m_Mesh->NumIndices(), 0, 0);
		}
	}

	bool Renderer::SetBuffers()
	{
		{	//	Vertices buffer
			D3D11_BUFFER_DESC buffer;
			buffer.Usage = D3D11_USAGE_IMMUTABLE;
			buffer.ByteWidth = sizeof MeshValue::VertexValue * m_Mesh->NumVertices();
			buffer.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			buffer.CPUAccessFlags = 0;
			buffer.MiscFlags = 0;
			buffer.StructureByteStride = 0;

			D3D11_SUBRESOURCE_DATA data;
			data.pSysMem = &m_Mesh->GetMeshValue()->Vertices[0];

			if (FAILED(DXRenderer::Get().GetDevice()->CreateBuffer(&buffer, &data, &m_Vertices)))
				return false;
		}

		{	//	Indices buffer
			D3D11_BUFFER_DESC buffer;
			buffer.Usage = D3D11_USAGE_IMMUTABLE;
			buffer.ByteWidth = sizeof UINT * m_Mesh->NumIndices();
			buffer.BindFlags = D3D11_BIND_INDEX_BUFFER;
			buffer.CPUAccessFlags = 0;
			buffer.MiscFlags = 0;
			buffer.StructureByteStride = 0;

			D3D11_SUBRESOURCE_DATA data;
			data.pSysMem = &m_Mesh->GetMeshValue()->Indices[0];

			if (FAILED(DXRenderer::Get().GetDevice()->CreateBuffer(&buffer, &data, &m_Indices)))
				return false;
		}

		return true;
	}

	bool Renderer::IASetup(LPCWSTR filePath)
	{
		if (!m_Mesh) return false;

		DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS;
		ID3D10Blob* pErrMsg = nullptr;

#if defined _DEBUG
		flags |= D3DCOMPILE_DEBUG;
		flags |= D3DCOMPILE_SKIP_OPTIMIZATION;
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
			return false;
		}

		m_Techniuque = m_Fx->GetTechniqueByName("Render");
		m_WorldVariable = m_Fx->GetVariableByName("World")->AsMatrix();
		m_ViewVariable = m_Fx->GetVariableByName("View")->AsMatrix();
		m_ProjectionVariable = m_Fx->GetVariableByName("Projection")->AsMatrix();

		D3D11_INPUT_ELEMENT_DESC elements[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, m_Mesh->NumIndices() / 3, D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};

		D3DX11_PASS_DESC pass;
		if (FAILED(m_Techniuque->GetPassByIndex(0)->GetDesc(&pass)))
		{
			MessageBox(nullptr, L"GetDesc error", L"Error", MB_OK);
			return false;
		}

		if (FAILED(DXRenderer::Get().GetDevice()->CreateInputLayout(
			elements,
			ARRAYSIZE(elements),
			pass.pIAInputSignature,
			pass.IAInputSignatureSize,
			&m_InputLayout)))
		{
			MessageBox(nullptr, L"IAInputLayout error", L"Error", MB_OK);
			return false;
		}

		return true;
	}
}

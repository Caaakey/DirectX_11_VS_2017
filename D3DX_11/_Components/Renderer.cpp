#include "stdafx.h"
#include "Renderer.h"

namespace Components
{
	Renderer::Renderer(ObjectModel* pConnect)
		: Component(pConnect),
		m_Mesh(nullptr), m_Material(nullptr), m_Fx(nullptr),
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
		SAFE_DELETE(m_Mesh);
		SAFE_DELETE(m_Material);

		SAFE_RELEASE(m_Fx);
		SAFE_RELEASE(m_InputLayout);
	}

	void Renderer::Update()
	{
	}

	void Renderer::Render()
	{
		UpdateMesh();
		UpdateMaterial();

		m_WorldVariable->SetMatrix((float*)transform->GetMatrix());
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

	void Renderer::UpdateMesh()
	{
		if (!m_Mesh) return;

		DXRenderer::Get().GetContext()->IASetInputLayout(m_InputLayout);
		DXRenderer::Get().GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		UINT stride = sizeof Renderers::MeshValue::VertexValue;
		UINT offset = 0;

		DXRenderer::Get().GetContext()->IASetVertexBuffers(0, 1, &m_Mesh->VerticesBuffer, &stride, &offset);
		DXRenderer::Get().GetContext()->IASetIndexBuffer(m_Mesh->IndicesBuffer, DXGI_FORMAT_R32_UINT, 0);
	}

	void Renderer::UpdateMaterial()
	{

	}

	HRESULT Renderer::SetBuffers()
	{
		if (!m_Mesh) return E_FAIL;

		return m_Mesh->IASet(DXRenderer::Get().GetDevice());
	}

	HRESULT Renderer::IASetup(LPCWSTR filePath)
	{
		if (!m_Mesh) return E_FAIL;

		DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS;
		ID3D10Blob* pErrMsg = nullptr;

#if defined _DEBUG
		flags |= D3DCOMPILE_DEBUG;
		flags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

		HRESULT hr = S_OK;
		hr = D3DX11CompileEffectFromFile(
			filePath,
			nullptr,
			D3D_COMPILE_STANDARD_FILE_INCLUDE,
			flags, 0,
			DXRenderer::Get().GetDevice(),
			&m_Fx,
			&pErrMsg);

		if (FAILED(hr))
		{
			MessageBox(nullptr, (LPCWSTR)pErrMsg->GetBufferPointer(), L"FX Compile error", MB_OK);

			SAFE_RELEASE(pErrMsg);
			return hr;
		}

		m_Techniuque = m_Fx->GetTechniqueByName("Render");
		m_WorldVariable = m_Fx->GetVariableByName("World")->AsMatrix();
		m_ViewVariable = m_Fx->GetVariableByName("View")->AsMatrix();
		m_ProjectionVariable = m_Fx->GetVariableByName("Projection")->AsMatrix();

		D3D11_INPUT_ELEMENT_DESC elements[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, m_Mesh->NumIndices() / 3, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, m_Mesh->NumVertices() / 2, D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};

		D3DX11_PASS_DESC pass;
		hr = m_Techniuque->GetPassByIndex(0)->GetDesc(&pass);

		if (FAILED(hr))
		{
			MessageBox(nullptr, L"GetPassByIndex pass is not found", L"Error", MB_OK);
			return hr;
		}

		hr = DXRenderer::Get().GetDevice()->CreateInputLayout(
			elements,
			ARRAYSIZE(elements),
			pass.pIAInputSignature,
			pass.IAInputSignatureSize,
			&m_InputLayout);

		if (FAILED(hr))
		{
			MessageBox(nullptr, L"IAInputLayout error", L"Error", MB_OK);
			return hr;
		}

		return hr;
	}
}

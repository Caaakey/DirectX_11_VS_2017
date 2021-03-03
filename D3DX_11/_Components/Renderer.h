#pragma once
#include "Renderer/Mesh.h"
#include "Renderer/Material.h"

namespace Components
{
	class Renderer : public Component
	{
	public:
		Renderer(Object* pConnect);
		~Renderer();

		void Release();
		void Update() override;
		void Render() override;

	private:
		Renderers::Mesh* m_Mesh;
		Renderers::Material* m_Material;

		ID3DX11Effect* m_Fx;
		ID3DX11EffectTechnique* m_Techniuque;
		ID3DX11EffectMatrixVariable* m_WorldVariable;
		ID3DX11EffectMatrixVariable* m_ViewVariable;
		ID3DX11EffectMatrixVariable* m_ProjectionVariable;

		ID3D11InputLayout* m_InputLayout;

		HRESULT SetBuffers();
		HRESULT IASetup(LPCWSTR filePath);

		void UpdateMesh();
		void UpdateMaterial();

	public:
		Renderers::Mesh* GetMesh() const { return m_Mesh; }
		void SetMesh(Renderers::Mesh* mesh)
		{
			if (m_Mesh) SAFE_DELETE(m_Mesh);
			m_Mesh = mesh;

			SetBuffers();
			IASetup(L"../_Shader/PixelShader.fx");
		}

		Renderers::Material* GetMaterial() const { return m_Material; }
		void SetMaterial(Renderers::Material* material)
		{
			if (m_Material) SAFE_DELETE(m_Material);
			m_Material = material;


		}
	};
}

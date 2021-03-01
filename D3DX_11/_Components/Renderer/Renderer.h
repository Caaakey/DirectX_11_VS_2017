#pragma once
#include "Mesh.h"

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
		Meshs::Mesh* m_Mesh;

		ID3DX11Effect* m_Fx;
		ID3D11Buffer* m_Vertices;
		ID3D11Buffer* m_Indices;
		ID3DX11EffectTechnique* m_Techniuque;
		ID3DX11EffectMatrixVariable* m_WorldVariable;
		ID3DX11EffectMatrixVariable* m_ViewVariable;
		ID3DX11EffectMatrixVariable* m_ProjectionVariable;

		ID3D11InputLayout* m_InputLayout;

		bool SetBuffers();
		bool IASetup(LPCWSTR filePath);

	public:
		Meshs::Mesh* GetMesh() const { return m_Mesh; }
		void SetMesh(Meshs::Mesh* mesh)
		{
			if (m_Mesh) Release();

			m_Mesh = mesh;
			SetBuffers();
			IASetup(L"../_Shader/PixelShader.fx");
		}
	};
}

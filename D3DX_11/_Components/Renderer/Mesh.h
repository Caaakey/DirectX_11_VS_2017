#pragma once
#include "Interfaces/IRenderer.h"

#if defined _DEBUG
#pragma comment(lib, "Effects11d.lib")
#else
#pragma comment(lib, "Effects11.lib")
#endif

#include <Dx11Effect/d3dx11effect.h>
#include <vector>

namespace Components
{
	namespace Renderers
	{
		struct MeshValue
		{
			struct VertexValue
			{
				VertexValue() {}
				VertexValue(
					float px, float py, float pz,
					float nx, float ny, float nz,
					float u, float v)
					: Position(px, py, pz), Normal(nx, ny, nz), TexC(u, v) { }

				VertexValue(const DirectX::XMFLOAT3& v, const DirectX::XMFLOAT3& n, const DirectX::XMFLOAT2& uv)
					: Position(v), Normal(n), TexC(uv) { }

				DirectX::XMFLOAT3 Position;
				DirectX::XMFLOAT3 Normal;
				DirectX::XMFLOAT2 TexC;
			};

			MeshValue() {}
			MeshValue(const VertexValue* v, const UINT vSize, const UINT* i, const UINT iSize)
			{
				Vertices = std::vector<VertexValue>(vSize);
				memcpy(&Vertices[0], v, sizeof VertexValue * vSize);

				Indices = std::vector<UINT>(iSize);
				memcpy(&Indices[0], i, sizeof UINT * iSize);
			}

			MeshValue(const std::vector<VertexValue>& v, const std::vector<UINT>& i)
				: Vertices(v), Indices(i)
			{}

			std::vector<VertexValue> Vertices;
			std::vector<UINT> Indices;
		};

		class Mesh : public IRenderer<MeshValue>
		{
		public:
			Mesh();
			Mesh(const MeshValue&);
			~Mesh();

			virtual void Release() override;
			virtual HRESULT ChangeVariable(ID3D11Device*, const MeshValue&) override;
			virtual HRESULT IASet(ID3D11Device*) override;

		private:
			MeshValue m_MeshValue;

		public:
			ID3D11Buffer* VerticesBuffer;
			ID3D11Buffer* IndicesBuffer;

			UINT NumVertices() const { return (UINT)m_MeshValue.Vertices.size(); }
			UINT NumIndices() const { return (UINT)m_MeshValue.Indices.size(); }

			MeshValue* GetMeshValue() { return &m_MeshValue; }
		};
	}
}


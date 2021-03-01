#pragma once
#include "System/Renderer/DXRenderer.h"

#pragma comment(lib, "Effects11d.lib")
#include <Dx11Effect/d3dx11effect.h>

#include "_Components/Base/Component.h"
#include <vector>

namespace Components
{
	namespace Meshs
	{
		struct MeshValue
		{
			struct VertexValue
			{
				VertexValue() {}
				VertexValue(const DirectX::XMFLOAT3 v, DirectX::XMFLOAT3 n, DirectX::XMFLOAT2 uv)
					: Vertex(v), Tex0(uv)
				{ }

				DirectX::XMFLOAT3 Vertex;
				DirectX::XMFLOAT3 Normal;
				DirectX::XMFLOAT2 Tex0;
			};

			MeshValue() {}
			MeshValue(const std::vector<VertexValue>& v, const std::vector<UINT>& i)
				: Vertices(v), Indices(i)
			{}

			std::vector<VertexValue> Vertices;
			std::vector<UINT> Indices;
		};

		class Mesh
		{
		public:
			Mesh();
			Mesh(const MeshValue& meshData);
			~Mesh();

		private:
			MeshValue m_MeshValue;

		public:
			UINT NumVertices() const { return (UINT)m_MeshValue.Vertices.size(); }
			UINT NumIndices() const { return (UINT)m_MeshValue.Indices.size(); }

			MeshValue* GetMeshValue() { return &m_MeshValue; }
		};
	}
}


#include "stdafx.h"
#include "Mesh.h"

namespace Components {
	namespace Renderers {

		Mesh::Mesh()
			: VerticesBuffer(nullptr), IndicesBuffer(nullptr)
		{
		}

		Mesh::Mesh(const MeshValue & meshData)
			: VerticesBuffer(nullptr), IndicesBuffer(nullptr),
			m_MeshValue(meshData)
		{

		}

		Mesh::~Mesh()
		{
			Release();
		}

		void Mesh::Release()
		{
			SAFE_RELEASE(VerticesBuffer);
			SAFE_RELEASE(IndicesBuffer);
		}

		HRESULT Mesh::ChangeVariable(ID3D11Device* device, const MeshValue& meshData)
		{
			Release();

			m_MeshValue = meshData;
			return IASet(device);
		}

		HRESULT Mesh::IASet(ID3D11Device* device)
		{
			HRESULT hr = S_OK;

			{	//	Vertices buffer
				D3D11_BUFFER_DESC buffer;
				buffer.Usage = D3D11_USAGE_IMMUTABLE;
				buffer.ByteWidth = sizeof Renderers::MeshValue::VertexValue * NumVertices();
				buffer.BindFlags = D3D11_BIND_VERTEX_BUFFER;
				buffer.CPUAccessFlags = 0;
				buffer.MiscFlags = 0;
				buffer.StructureByteStride = 0;

				D3D11_SUBRESOURCE_DATA data;
				data.pSysMem = &m_MeshValue.Vertices[0];

				hr = device->CreateBuffer(&buffer, &data, &VerticesBuffer);
				if (FAILED(hr)) return hr;
			}

			{	//	Indices buffer
				D3D11_BUFFER_DESC buffer;
				buffer.Usage = D3D11_USAGE_IMMUTABLE;
				buffer.ByteWidth = sizeof UINT * NumIndices();
				buffer.BindFlags = D3D11_BIND_INDEX_BUFFER;
				buffer.CPUAccessFlags = 0;
				buffer.MiscFlags = 0;
				buffer.StructureByteStride = 0;

				D3D11_SUBRESOURCE_DATA data;
				data.pSysMem = &m_MeshValue.Indices[0];

				hr = device->CreateBuffer(&buffer, &data, &IndicesBuffer);
				if (FAILED(hr)) return hr;
			}

			return hr;
		}
	}

}

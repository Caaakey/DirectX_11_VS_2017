#include "stdafx.h"
#include "Mesh.h"

namespace Components {
	namespace Meshs {

		Mesh::Mesh()
		{
		}

		Mesh::Mesh(const MeshValue & meshData)
			: m_MeshValue(meshData)
		{

		}

		Mesh::~Mesh()
		{
		}

	}
}

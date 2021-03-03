#include "stdafx.h"
#include "Material.h"

namespace Components
{
	namespace Renderers
	{
		Material::Material()
			: m_MainTexture(nullptr)
		{
		}

		Material::~Material()
		{
			SAFE_DELETE(m_MainTexture);
		}
	}
}
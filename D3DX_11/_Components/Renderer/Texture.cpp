#include "stdafx.h"
#include "Texture.h"

namespace Components
{
	namespace Renderers
	{
		Texture::Texture()
			: m_DiffuseSRV(nullptr), m_DiffuseVariable(nullptr)
		{

		}

		Texture::~Texture()
		{
			SAFE_RELEASE(m_DiffuseSRV);
		}

		void Texture::SetResource()
		{
			if (m_DiffuseVariable) m_DiffuseVariable->SetResource(m_DiffuseSRV);
		}
	}
}

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

		void Material::IASet()
		{
			if (!m_MainTexture) return;

			m_MainTexture->SetResource();
		}

		bool Material::LoadTexture(std::wstring filePath, ID3DX11Effect* pFx)
		{
			if (m_MainTexture) SAFE_DELETE(m_MainTexture);

			m_MainTexture = new Texture(filePath);

			if (!m_MainTexture->GetDiffuseSRV())
			{
				SAFE_DELETE(m_MainTexture);
				return false;
			}
			else
			{
				m_MainTexture->SetVariable(pFx);
			}

			return true;
		}

	}
}
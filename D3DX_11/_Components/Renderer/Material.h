#pragma once
#include "Interfaces/IRenderer.h"
#include "Texture.h"

namespace Components
{
	namespace Renderers
	{
		class Material
		{
		public:
			Material();
			~Material();

			void IASet();

		private:
			Texture* m_MainTexture;

		public:
			Texture* MainTexture() const { m_MainTexture; }
			bool LoadTexture(std::wstring filePath, ID3DX11Effect* pFx);

		};
	}
}

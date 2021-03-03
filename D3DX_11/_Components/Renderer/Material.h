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

		private:
			Texture* m_MainTexture;

		};
	}
}

#pragma once
#include "Interfaces/IRenderer.h"

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
			ID3D11ShaderResourceView* m_DiffuseSRVTexture;
			ID3DX11EffectShaderResourceVariable* m_DiffuseTexVariable;

		};
	}
}

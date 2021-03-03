#pragma once

namespace Components
{
	namespace Renderers
	{
		class Texture
		{
		public:
			Texture();
			~Texture();

			void SetResource();

		private:
			ID3D11ShaderResourceView* m_DiffuseSRV;

		private:
			ID3DX11EffectShaderResourceVariable* m_DiffuseVariable;

		};
	}
}

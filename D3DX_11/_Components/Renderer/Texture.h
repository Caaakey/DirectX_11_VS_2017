#pragma once

namespace Components
{
	namespace Renderers
	{
		class Texture
		{
		public:
			Texture() = delete;
			Texture(std::wstring filePath);
			~Texture();

			void SetResource();
			void SetVariable(ID3DX11Effect* pFx);
			ID3D11ShaderResourceView* GetDiffuseSRV() const { return m_DiffuseSRV; }

		private:
			ID3D11ShaderResourceView* m_DiffuseSRV;

		private:
			ID3DX11EffectShaderResourceVariable* m_DiffuseVariable;

		};
	}
}


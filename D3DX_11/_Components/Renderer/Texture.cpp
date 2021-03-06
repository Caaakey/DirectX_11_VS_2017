#include "stdafx.h"
#include "Texture.h"

#pragma comment(lib, "DirectXTex.lib")
#include <DirectXTex.h>

namespace Components
{
	namespace Renderers
	{
		Texture::Texture(std::wstring filePath)
			: m_DiffuseSRV(nullptr), m_DiffuseVariable(nullptr)
		{
			HRESULT hr = S_OK;
			DirectX::ScratchImage image;

			WCHAR ext[_MAX_EXT] = { 0, };
			_wsplitpath_s(filePath.c_str(), nullptr, 0, nullptr, 0, nullptr, 0, ext, _MAX_EXT);

			if (_wcsicmp(ext, L".dds") == 0)
			{
				hr = DirectX::LoadFromDDSFile(filePath.c_str(), DirectX::DDS_FLAGS_NONE, nullptr, image);
			}
			else if (_wcsicmp(ext, L".tga") == 0)
			{
				hr = DirectX::LoadFromTGAFile(filePath.c_str(), nullptr, image);
			}
			else
			{
				hr = DirectX::LoadFromWICFile(filePath.c_str(), DirectX::WIC_FLAGS_NONE, nullptr, image);
			}

			if (FAILED(hr)) return;

			hr = DirectX::CreateShaderResourceView(
				DXRenderer::Get().GetDevice(),
				image.GetImages(),
				image.GetImageCount(),
				image.GetMetadata(),
				&m_DiffuseSRV);

			if (FAILED(hr)) return;
		}

		Texture::~Texture()
		{
			SAFE_RELEASE(m_DiffuseSRV);
		}

		void Texture::SetResource()
		{
			if (m_DiffuseVariable) m_DiffuseVariable->SetResource(m_DiffuseSRV);
		}

		void Texture::SetVariable(ID3DX11Effect * pFx)
		{
			m_DiffuseVariable = pFx->GetVariableByName("diffuseTex")->AsShaderResource();
		}
	}
}

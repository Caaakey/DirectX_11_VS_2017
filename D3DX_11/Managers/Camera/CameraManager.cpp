#include "stdafx.h"
#include "CameraManager.h"

CameraManager::CameraManager()
{
	m_Eye = DirectX::XMVectorSet(0.0f, 0.0f, -10.0f, 1.0f);
	m_Look = DirectX::XMVectorZero();
	m_Up = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	D3D11_VIEWPORT viewPort = { 0, };
	viewPort.Width = static_cast<FLOAT>(Application::Get().Width);
	viewPort.Height = static_cast<FLOAT>(Application::Get().Height);
	viewPort.MinDepth = 0.0f;
	viewPort.MaxDepth = 1.0f;

	DXRenderer::Get().GetContext()->RSSetViewports(1, &viewPort);

	DirectX::XMMATRIX view = DirectX::XMMatrixLookAtLH(m_Eye, m_Look, m_Up);
	DirectX::XMStoreFloat4x4(&m_View, view);

	DirectX::XMMATRIX proj = DirectX::XMMatrixPerspectiveFovLH(
		0.25f * DirectX::XM_PI,
		Application::Get().AspectRatio(),
		0.01f,
		1000.0f);
	DirectX::XMStoreFloat4x4(&m_Proj, proj);
}

CameraManager::~CameraManager()
{
}

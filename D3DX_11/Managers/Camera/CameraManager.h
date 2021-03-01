#pragma once

class CameraManager
{
public:
	static CameraManager& Get() {
		static CameraManager instance;
		return instance;
	}

	CameraManager();
	CameraManager(CameraManager const&) = delete;
	~CameraManager();

	void operator=(CameraManager const&) = delete;

public:
	DirectX::XMVECTOR m_Eye;
	DirectX::XMVECTOR m_Look;
	DirectX::XMVECTOR m_Up;

	DirectX::XMFLOAT4X4 m_View;
	DirectX::XMFLOAT4X4 m_Proj;

public:
	DirectX::XMMATRIX GetViewMatrix() const { return DirectX::XMLoadFloat4x4(&m_View); }
	DirectX::XMMATRIX GetProjMatrix() const { return DirectX::XMLoadFloat4x4(&m_Proj); }
	DirectX::XMMATRIX GetWVP(DirectX::XMMATRIX world)
	{
		return world * GetViewMatrix() * GetProjMatrix();
	}
};

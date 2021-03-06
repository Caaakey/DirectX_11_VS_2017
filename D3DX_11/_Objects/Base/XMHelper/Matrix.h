#pragma once

namespace Vectors
{
	class Matrix
	{
	public:
		Matrix()
		{
			SetMatrix(DirectX::XMMatrixIdentity());
		}
		~Matrix() {}

	private:
		//	Do not change the order!!
		DirectX::XMMATRIX m_Matrix;
		DirectX::XMFLOAT4X4 m_Float4x4;

	public:
		DirectX::XMMATRIX* GetMatrix() { return &m_Matrix; }
		void SetMatrix(const DirectX::XMMATRIX& matrix)
		{
			m_Matrix = matrix;
			DirectX::XMStoreFloat4x4(&m_Float4x4, matrix);
		}
		void SetMatrix(const DirectX::XMFLOAT4X4& mat4x4)
		{
			m_Float4x4 = mat4x4;
			m_Matrix = DirectX::XMLoadFloat4x4(&mat4x4);
		}

	};
}

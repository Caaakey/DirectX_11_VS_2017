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
		DirectX::XMMATRIX m_Matrix;
		DirectX::XMFLOAT4X4 m_Float4x4;

	public:
		DirectX::XMMATRIX* GetMatrix() { return &m_Matrix; }
		void SetMatrix(const DirectX::XMMATRIX& matrix)
		{
			m_Matrix = matrix;
			DirectX::XMStoreFloat4x4(&m_Float4x4, matrix);
		}

	};
}

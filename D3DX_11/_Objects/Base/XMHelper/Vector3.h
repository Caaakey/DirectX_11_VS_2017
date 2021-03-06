#pragma once

namespace Vectors
{
	class Vector3
	{
	public:
		Vector3() : m_Vector(DirectX::XMVectorZero()), m_Float(0, 0, 0) {}
		Vector3(float x, float y, float z) { Set(x, y, z); }
		Vector3(const DirectX::XMFLOAT3& vec) { Set(vec.x, vec.y, vec.z); }
		Vector3(const Vector3& vec)
			: m_Float(vec.m_Float), m_Vector(vec.m_Vector) { }

		~Vector3() {}

		void Set(const float x, const float y, const float z)
		{
			m_Float = DirectX::XMFLOAT3(x, y, z);
			m_Vector = DirectX::XMVectorSet(x, y, z, 0);
		}

	private:
		DirectX::XMVECTOR m_Vector;
		DirectX::XMFLOAT3 m_Float;

	public:
		const float& operator[](int index) const
		{
			switch (index)
			{
			case 0: return m_Float.x;
			case 1: return m_Float.y;
			case 2: return m_Float.z;
			}

			throw std::exception();
		}
		float& operator[](int index)
		{
			Vector3* pVector = this;

			switch (index)
			{
			case 0: return pVector->m_Float.x;
			case 1: return pVector->m_Float.y;
			case 2: return pVector->m_Float.z;
			}

			throw std::exception();
		}
		Vector3 operator+(const Vector3& vec)
		{
			float x = this->m_Float.x + vec.m_Float.x;
			float y = this->m_Float.y + vec.m_Float.y;
			float z = this->m_Float.z + vec.m_Float.z;

			return Vector3(x, y, z);
		}
		Vector3 operator-(const Vector3& vec)
		{
			float x = this->m_Float.x - vec.m_Float.x;
			float y = this->m_Float.y - vec.m_Float.y;
			float z = this->m_Float.z - vec.m_Float.z;

			return Vector3(x, y, z);
		}
		Vector3 operator*(const Vector3& vec)
		{
			float x = this->m_Float.x * vec.m_Float.x;
			float y = this->m_Float.y * vec.m_Float.y;
			float z = this->m_Float.z * vec.m_Float.z;

			return Vector3(x, y, z);
		}
		Vector3 operator/(const Vector3& vec)
		{
			float x = this->m_Float.x / vec.m_Float.x;
			float y = this->m_Float.y / vec.m_Float.y;
			float z = this->m_Float.z / vec.m_Float.z;

			Set(x, y, z);
			return *this;
		}
		Vector3 operator=(const DirectX::XMFLOAT3& vec)
		{
			Set(vec.x, vec.y, vec.z);
			return *this;
		}

		explicit operator DirectX::XMFLOAT3() const { return m_Float; }

		DirectX::XMVECTOR& GetVector() { return m_Vector; }
	};

}

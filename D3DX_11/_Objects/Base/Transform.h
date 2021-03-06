#pragma once
#include <DirectXMath.h>
#include "Utility/DefineUtility.h"

#include "XMHelper/Vector3.h"
#include "XMHelper/Matrix.h"
using namespace Vectors;

class Transform
{
public:
	Transform();
	~Transform();

public:
	Vector3 Position;
	Vector3 Rotation;
	Vector3 Scale;

private:
	Matrix m_WorldMat;

public:
	DirectX::XMMATRIX* GetMatrix();

	void SetMatrix(const DirectX::XMMATRIX& matrix) { m_WorldMat.SetMatrix(matrix); }
	void SetMatrix(const DirectX::XMFLOAT4X4& mat4x4) { m_WorldMat.SetMatrix(mat4x4); }

};

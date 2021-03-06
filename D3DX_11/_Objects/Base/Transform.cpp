#include "stdafx.h"
#include "Transform.h"

Transform::Transform()
	: Position(), Rotation(), Scale(1, 1, 1),
	m_WorldMat()
{
}

Transform::~Transform()
{
}

DirectX::XMMATRIX * Transform::GetMatrix()
{
	DirectX::XMMATRIX mat = DirectX::XMMatrixIdentity() *
		DirectX::XMMatrixScaling(Scale[0], Scale[1], Scale[2]) *
		DirectX::XMMatrixTranslation(Position[0], Position[1], Position[2]) *
		DirectX::XMMatrixRotationRollPitchYaw(Rotation[1], Rotation[0], Rotation[2]);

	return &mat;
}

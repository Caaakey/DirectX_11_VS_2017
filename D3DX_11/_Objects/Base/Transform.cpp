#include "Transform.h"
#include "stdafx.h"

Transform::Transform()
{
	Position = DirectX::XMVectorZero();
	Rotation = DirectX::XMVectorZero();
	Scale = DirectX::XMVectorSet(1, 1, 1, 0);

	WorldMatrix = DirectX::XMMatrixIdentity();
}

Transform::~Transform()
{
}

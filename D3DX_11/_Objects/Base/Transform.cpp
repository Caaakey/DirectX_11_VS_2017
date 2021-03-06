#include "stdafx.h"
#include "Transform.h"

Transform::Transform()
	: Position(), Rotation(), Scale(1, 1, 1),
	WorldMat()
{
}

Transform::~Transform()
{
}

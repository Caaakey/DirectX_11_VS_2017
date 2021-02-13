#pragma once
#include <DirectXMath.h>
#include "Utility/DefineUtility.h"

class Transform
{
public:
	Transform();
	~Transform();

private:
	Property(DirectX::XMVECTOR, Position)
	Property(DirectX::XMVECTOR, Rotation)
	Property(DirectX::XMVECTOR, Scale)

	Property(DirectX::XMMATRIX, WorldMatrix)
public:
	
};


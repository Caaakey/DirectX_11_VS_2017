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

	Matrix WorldMat;

};

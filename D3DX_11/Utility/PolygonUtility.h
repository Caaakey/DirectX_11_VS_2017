#pragma once
#include "_Components/Renderer/Mesh.h"

using namespace Components;
using namespace Renderers;

class PolygonUtility
{
public:
	static Mesh* CreateBox(DirectX::XMFLOAT3 scale);

};


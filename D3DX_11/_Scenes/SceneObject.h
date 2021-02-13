#pragma once
#include "Interface/IScene.h"

class SceneObject : public IScene
{
public:
	SceneObject(const std::string name)
	{
		Name = name;
		Enable = true;
		
		m_WorldMatrix = DirectX::XMMatrixIdentity();
	}

	virtual ~SceneObject() {}

private:
	Property(bool, Enable)
	Property(std::string, Name)
	Property(DirectX::XMMATRIX, WorldMatrix)
};